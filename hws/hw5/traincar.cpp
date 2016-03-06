// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//


void TotalWeightAndCountCars(TrainCar* & train,int & total_weight,int & num_engines, 
                            int & num_freight_cars,int & num_passenger_cars,
                            int & num_dining_cars,int & num_sleeping_cars) {
  total_weight=num_engines=num_freight_cars=num_passenger_cars=num_dining_cars=num_sleeping_cars=0;
  TrainCar* tmp = train;
  while (tmp != NULL) {
    total_weight += tmp->getWeight();
    if (tmp->isEngine()==true) {
      num_engines++;
    }
    else if (tmp->isFreightCar()==true) {
      num_freight_cars++;
    }
    else if (tmp->isPassengerCar()==true) {
      num_passenger_cars++;
    }
    else if (tmp->isDiningCar()==true) {
      num_dining_cars++;
    }
    else if (tmp->isSleepingCar()==true) {
      num_sleeping_cars++;
    }
    tmp = tmp->next;
  }
}

float CalculateSpeed(TrainCar* & train) {
  int total_weight,num_engines,num_freight_cars,num_passenger_cars,num_dining_cars,num_sleeping_cars;
  TotalWeightAndCountCars(train,total_weight,num_engines,num_freight_cars,
                          num_passenger_cars,num_dining_cars,num_sleeping_cars);
  int hp = num_engines*3000;
  return ((hp*550.0*3600.0)/((20.0/.01)*.02*5280.0*total_weight));
}

float AverageDistanceToDiningCar(TrainCar* & train) {
  int total_weight,num_engines,num_freight_cars,num_passenger_cars,num_dining_cars,num_sleeping_cars;
  TotalWeightAndCountCars(train,total_weight,num_engines,num_freight_cars,
                          num_passenger_cars,num_dining_cars,num_sleeping_cars);
  if (num_dining_cars==0) {
    return -1;
  }
  else {
    float sum_distances = 0;
    float f_distance, b_distance;
    bool b_found, f_found;
    TrainCar* tmp = train;
    TrainCar* car;
    while (tmp!=NULL) {
      if (tmp->isPassengerCar()==true) {
        TrainCar* tmp2 = tmp;
        b_found = f_found = false;
        f_distance = b_distance = 0;
        car = tmp2;
        while (tmp2!=NULL) { //forward
          if (tmp2->isEngine()==true) { //blocked by engine
            break;
          }
          else if (tmp2->isDiningCar()==true) { //found dining car
            f_found = true;
            break;
          }
          else { //keep movin'
            f_distance++;
            tmp2=tmp2->next;
          }
        }
        tmp2 = car;
        while (tmp2!=NULL) { //backwards
          if (tmp2->isEngine()==true) { //blocked by engine
            break;
          }
          else if (tmp2->isDiningCar()==true) { //found dining car
            b_found = true;
            break;
          }
          else { //keep movin'
            b_distance++;
            tmp2=tmp2->prev;
          }
        }
        if (b_found==false and f_found==false) { //no dining car found
          return -1;
        }
        else if (b_found==true and f_found==true) { //found both directions, average the two
          if (f_distance<b_distance) {
            sum_distances += f_distance;
          }
          else {
            sum_distances += b_distance;
          }
        }
        else if (f_found==true and b_found==false) { //found forward
          sum_distances += f_distance;
        }
        else if (f_found==false and b_found==true) { //found backwards
          sum_distances += b_distance;
        }
      }
      tmp = tmp->next;
    }
    return (sum_distances/((float)(num_passenger_cars)));
  }
}
int ClosestEngineToSleeperCar(TrainCar* train) {
  int total_weight,num_engines,num_freight_cars,num_passenger_cars,num_dining_cars,num_sleeping_cars;
  TotalWeightAndCountCars(train,total_weight,num_engines,num_freight_cars,
                          num_passenger_cars,num_dining_cars,num_sleeping_cars);
  float sum_distances = 0;
  float f_distance, b_distance;
  bool b_found, f_found;
  TrainCar* tmp = train;
  TrainCar* car;
  if (num_engines==0) {
    return -1;
  }
  while (tmp!=NULL) {
    if (tmp->isSleepingCar()==true) {
      TrainCar* tmp2 = tmp;
      b_found = f_found = false;
      f_distance = b_distance = 0;
      car = tmp2;
      while (tmp2!=NULL) { //forward
        if (tmp2->isEngine()==true) { //found engine
          f_found = true;
          break;
        }
        else { //keep movin'
          f_distance++;
          tmp2=tmp2->next;
        }
      }
      tmp2 = car;
      while (tmp2!=NULL) { //backwards
        if (tmp2->isEngine()==true) { //found engine
          b_found = true;
          break;
        }
        else { //keep movin'
          b_distance++;
          tmp2=tmp2->prev;
        }
      }
      if (b_found==false and f_found==false) { //no engine found
        return -1;
      }
      else if (b_found==true and f_found==true) { //found both directions, average the two
        if (f_distance<b_distance) {
          sum_distances += f_distance;
        }
        else {
          sum_distances += b_distance;
        }
      }
      else if (f_found==true and b_found==false) { //found forward
        sum_distances += f_distance;
      }
      else if (f_found==false and b_found==true) { //found backwards
        sum_distances += b_distance;
      }
    }
    tmp = tmp->next;
  }
  return (sum_distances/((float)(num_sleeping_cars)));
}

void PushBack(TrainCar* & train, TrainCar* n) {
  if (train==NULL) {
    train =n;
  }
  else if (n==NULL) {}
  else {
    TrainCar* tmp;
    tmp = train;
    while (tmp!=NULL) {
      if (tmp->next==NULL) {
        break;
      }
      else {
        tmp = tmp->next;
      }
    }
    tmp->next = n;
    n->prev = tmp;
  }
}

void PushFront(TrainCar* & train, TrainCar* n) { //add one car to front
  if (train==NULL) {
    train = n;
  }
  else {
    n->next = train;
    train->prev = n;
    train = n;
  }
}

void DeleteAllCars(TrainCar* & train) {
  while (train!=NULL) {
    if (train->next==NULL) {
      delete train;
      break;
    }
    else {
      train=train->next;
      delete train->prev;
    }
  }
}

std::vector<TrainCar*> ShipFreight(TrainCar* & engines, TrainCar* & freight, 
                                  float min_speed, int max_cars) {
  std::vector<TrainCar*> trains;
  int num_engines =0;
  TrainCar* tmp = engines;
  float speed;
  while (tmp!=NULL) {
    num_engines++;
    tmp = tmp->next;
  }
  int num_freight_cars=0;
  tmp = freight;
  while (tmp!=NULL) {
    num_freight_cars++;
    tmp = tmp->next;
  }
  while (num_engines>0 and num_freight_cars>0) {
    int num_cars =0;
    TrainCar* temp_train = NULL;
    while (num_cars<max_cars and num_engines>0 and num_freight_cars>0) {
      if (temp_train==NULL) {
        PushFront(temp_train, PopLastCar(engines));
        num_engines--;
        num_cars++;
      }
      speed = CalculateSpeed(temp_train);
      if (speed<min_speed) {
        PushFront(temp_train, PopLastCar(engines));
        num_engines--;
        num_cars++;
      }
      else {
        PushBack(temp_train, PopLastCar(freight));
        num_freight_cars--;
        num_cars++;
      }      
    }
    speed = CalculateSpeed(temp_train);
    if (speed<min_speed) {
      PushBack(freight, PopLastCar(temp_train));
    }
    trains.push_back(temp_train);
  }
  return trains;
}

TrainCar* PopLastCar(TrainCar* & train) { //remove last car and return it
  TrainCar* tmp = train;
  TrainCar* second_to_last;
  TrainCar* last;
  while (tmp!=NULL) {
    if (tmp->next==NULL and tmp->prev==NULL) { //train only has one node
      train=NULL;
      break;
    }      
    else if (tmp->next==NULL) { //point to last car
      last = tmp;
    }    
    else if (tmp->next->next==NULL) {
      second_to_last = tmp;
    }
    tmp = tmp->next;
  }
  if (train==NULL) {
    last = tmp;
  }
  else {
    last->prev = NULL;
    second_to_last->next = NULL;
  }
  return last;
}
TrainCar* PopFrontCar(TrainCar* & train) {
  TrainCar* tmp = train;
  if (tmp->next==NULL and tmp->prev==NULL) {
    train = NULL;
    return tmp;
  }
  else {
    train = train->next;
    train->prev = NULL;
    tmp->next = NULL;
    return tmp;
  }
}

TrainCar* PopCar(TrainCar* & train, const int & ID) { //assumes valid ID
  TrainCar* tmp = train;
  TrainCar* prev;
  TrainCar* next;
  while (tmp!=NULL) {
    if (tmp->getID()==ID) {
      break;
    }
    else {
      tmp = tmp->next;
    }
  }
  if (tmp->next==NULL and tmp->prev==NULL) {
    train=NULL;
    return tmp;
  }
  else if (tmp->next==NULL) {
    prev = tmp->prev;
    prev->next = NULL;
    tmp->prev = NULL;
    return tmp;
  }
  else if (tmp->prev==NULL) {
    next = tmp->next;
    next->prev = NULL;
    tmp->next = NULL;
    train = next;
    return tmp;
  }
  else {
    prev = tmp->prev;
    next = tmp->next;
    prev->next = next;
    next->prev = prev;
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
  }
}

void Separate(TrainCar* & original, TrainCar* & t2, TrainCar* & t3) {
  int total_weight,num_engines,num_freight_cars,num_passenger_cars,num_dining_cars,num_sleeping_cars;
  TotalWeightAndCountCars(original,total_weight,num_engines,num_freight_cars,
                          num_passenger_cars,num_dining_cars,num_sleeping_cars);
  //following splits train in half
  TrainCar* tmp = original;
  TrainCar* tmp2;
  original = NULL;
  t2 = tmp;
  int half = (num_engines+num_sleeping_cars+num_passenger_cars+num_dining_cars)/2;
  for (int i=0;i<half;i++) {
    tmp = tmp->next;
  }
  t3 = tmp;
  tmp->prev->next = NULL;
  tmp->prev = NULL;
  int t2_engines, t3_engines, t2_other, t3_other; //amount of engines/other on each train
  t2_engines=t3_engines=t2_other=t3_other=0; //set all initially to zero

  tmp = t2;
  while (tmp!=NULL) { //count for first train
    if (tmp->isEngine()==true) {
      t2_engines++;
    }
    else {
      t2_other++;
    }
    tmp=tmp->next;
  }

  tmp = t3;
  while (tmp!=NULL) { //count for second train
    if (tmp->isEngine()==true) {
      t3_engines++;
    }
    else {
      t3_other++;
    }
    tmp=tmp->next;
  }
  if (t2_engines<(num_engines/2)) { //not enough engines on first train
    tmp = t3;
    while (t2_engines<(num_engines/2)) {
      if (tmp->isEngine()==true) {
        PushBack(t2, PopCar(t3, tmp->getID()));
        t2_engines++;
        t3_engines--;
        tmp2 = t2;
        while (tmp2!=NULL) {
          if (tmp2->next==NULL) {
            break;
          }
          else {
            tmp2 = tmp2->next;
          }
        }
        while (tmp2!=NULL) { //add passenger car to second train to make up for loss of engine
          if (tmp2->isEngine()==false) {
            PushFront(t3, PopCar(t2, tmp2->getID()));
            t2_other--;
            t3_other++;
            break;
          }
          tmp2= tmp2->prev;
        }
      }
      tmp = tmp->next;
    }
  }
  
  else if (t3_engines<(num_engines/2)) { //not enough engines on second train
    tmp = t2;
    while (tmp!=NULL) { //start at end of first train for shorter moving distance
      if (tmp->next==NULL) {
        break;
      }
      else {
        tmp = tmp->next;
      }
    }
    while (t3_engines<(num_engines/2)) {
      if (tmp->isEngine()==true) {
        PushFront(t3, PopCar(t2, tmp->getID()));
        t3_engines++;
        t2_engines--;
        tmp2 = t3;
        while (tmp2!=NULL) {
          if (tmp2->isEngine()==false) {
            PushBack(t2, PopCar(t3, tmp2->getID()));
            t3_other--;
            t2_other++;
            break;
          }
          tmp2 = tmp2->next;
        }
      }
      tmp = tmp->prev;
    }
  }

}