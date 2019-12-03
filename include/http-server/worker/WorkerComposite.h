//
// Created by Julia on 2019-12-02.
//

#ifndef HTTP_SERVER_BUILDINGCOMPOSITE_H
#define HTTP_SERVER_BUILDINGCOMPOSITE_H

#include<vector>
#include "WorkerComponent.h"
class WorkerComposite : WorkerComponent{
private:
    std::vector<WorkerComponent> workerComponents;
public:
   float GetSumOfSalaries();

};


#endif //HTTP_SERVER_BUILDINGCOMPOSITE_H
