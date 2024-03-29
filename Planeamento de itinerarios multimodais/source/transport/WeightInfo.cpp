#include "WeightInfo.h"�
#include <iostream>

double WeightInfo::timeWeight = 0;
double WeightInfo::distanceWeight = 0;
double WeightInfo::switchWeight = 0;
double WeightInfo::costWeight = 0;

double WeightInfo::getWeight() const{
	return cost*costWeight + distance * distanceWeight + switchs * switchWeight + time * timeWeight;
}

double WeightInfo::getCost() const {
	return cost;
}

void WeightInfo::setCost(double cost) {
	this->cost = cost;
}

double WeightInfo::getCostWeight() {
	return costWeight;
}

void WeightInfo::setCostWeight(double costWeight) {
	WeightInfo::costWeight = costWeight;
}

double WeightInfo::getDistance() const {
	return distance;
}

void WeightInfo::setDistance(double distance) {
	this->distance = distance;
}

double WeightInfo::getDistanceWeight() {
	return distanceWeight;
}

void WeightInfo::setDistanceWeight(double distanceWeight) {
	WeightInfo::distanceWeight = distanceWeight;
}

double WeightInfo::getSwitchs() const {
	return switchs;
}

void WeightInfo::setSwitchs(double switchs) {
	this->switchs = switchs;
}

double WeightInfo::getSwitchWeight() {
	return switchWeight;
}

void WeightInfo::setSwitchWeight(double switchWeight) {
	WeightInfo::switchWeight = switchWeight;
}

double WeightInfo::getTime() const {
	return time;
}

void WeightInfo::setTime(double time) {
	this->time = time;
}

double WeightInfo::getTimeWeight() {
	return timeWeight;
}

void WeightInfo::setTimeWeight(double timeWeight) {
	WeightInfo::timeWeight = timeWeight;
}

WeightInfo WeightInfo::operator+(const WeightInfo& w) const
{
	WeightInfo ret;
	ret.cost = this->cost;
	ret.time = this->time;
	ret.distance = this->distance;
	ret.switchs = this->switchs;

	ret.cost += w.cost;
	ret.time += w.time;
	ret.distance += w.distance;
	ret.switchs += w.switchs;

	return ret;
}

std::ostream& operator<<(std::ostream& os, WeightInfo& w)
{
	os << "Time: " << Hour(w.getTime()) << std::endl;
	os << "Monetary cost: " << w.getCost() << " euros" << std::endl;
	os << "Distance: " << w.getDistance() / 1000 << "km" << std::endl;
	os << "Number of transport switches: " << w.getSwitchs() << std::endl;
	return os;
}
