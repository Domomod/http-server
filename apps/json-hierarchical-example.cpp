//
// Created by dominik on 05.11.19.
//

/* This file show's an examplary json polimorphic serialization and deserialization of hierarchical structures.
 * To perform this task I used an MIT-Licensed library "Json for Modern C++" by nlohmann.
 * "Json for Modern C++" repository: https://github.com/nlohmann/json#arbitrary-types-conversions
 * */

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class A;

class B;

void to_json(json &j, const std::shared_ptr<A> &a);

void from_json(const json &j, std::shared_ptr<A> &a);

class A
{
public:
    std::string name;
    std::shared_ptr<A> child = nullptr;

    class JsonDeserializer;

    virtual void to_json(json &j) const
    {
        j["name"] = name;
        j["@type"] = "A";
        if (child != nullptr)
            j["child"] = child;
        else
            j["child"] = nullptr;
    }

    virtual void from_json(const json &j)
    {
        j.at("name").get_to(name);
        try
        {
            auto x = j.at("child");
            if (!x.is_null())
            {
                x.get_to(child);
            }
        }
        catch (...)
        {
        }
    }
};

class B : public A
{
public:
    int x;

    void to_json(json &j) const override
    {
        A::to_json(j);
        j["@type"] = "B";
        j["x"] = x;
    }

    void from_json(const json &j) override
    {
        A::from_json(j);
        j.at("x").get_to(x);
    }
};


void to_json(json &j, const std::shared_ptr<A> &a)
{
    a->to_json(j);
}

void from_json(const json &j, std::shared_ptr<A> &a)
{
    std::string type;
    try
    {
        j.at("@type").get_to(type);
        if (type == "B")
            a.reset(new B());
        if (type == "A")
            a.reset(new A());

        a->from_json(j);
    }
    catch (...)
    {
        a.reset();
        throw std::runtime_error("Incorrect Json: Neither valid A or it's subclass representation.");
    }
}

int main(int argc, char *argv[])
{
    auto j = R"(
      {
        "@type" : "A",
        "name" : "Albert",
        "child" :   {
                        "@type" : "A",
                        "name" : "Carl",
                        "child" :   {
                                        "@type" : "B",
                                        "name" : "Joe",
                                        "child" : null,
                                        "x" : 3
                                    }
                    }
      }
    )"_json;

    std::shared_ptr<A> a;
    j.get_to(a);

    json j2 = a;
    std::cout << j2.dump(2);
    return 0;
}