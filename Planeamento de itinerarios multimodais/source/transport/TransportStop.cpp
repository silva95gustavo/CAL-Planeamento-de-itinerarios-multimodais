/*
 * TransportStop.cpp
 *
 *  Created on: 02/04/2015
 *      Author: Gustavo
 */

#include "TransportStop.h"
#include "WeightInfo.h"
#include <algorithm>

using namespace std;

Coordinates TransportStopDistCompare::reference = Coordinates(0, 0);

TransportStop::TransportStop(const std::string &name, const Coordinates &coords):
	Vertex(coords), name(name)
{
}

void TransportStop::addHour(const Hour &hour)
{
	schedule.push_back(hour);
}

TransportRoute *TransportStop::getTransportRoute() const
{
	return transportRoute;
}

const vector<Hour> &TransportStop::getSchedule() const
{
	return schedule;
}

void TransportStop::setTransportRoute(TransportRoute *transportRoute)
{
	this->transportRoute = transportRoute;
}

bool TransportStop::operator==(const TransportStop &transportStop) const
{
	return name == transportStop.name;
}

double TransportStop::calculateH(Vertex * v) const
{
	TransportStop* ts = dynamic_cast<TransportStop*>(v);
	if(ts == NULL)
		return 0;
	double dist = this->getCoords().calcDist(v->getCoords());

	return dist / TransportSpeeds::getMaxSpeed() * WeightInfo::getTimeWeight() + dist*WeightInfo::getDistanceWeight();
}

TransportStop::~TransportStop()
{

}


void TransportStop::userAddToGraph(Graph* g){
	TransportStopDistCompare::reference = this->getCoords();
	priority_queue<TransportStop *, vector<TransportStop *>, TransportStopDistCompare> transportStops;
	vector<Vertex*> verts = g->getVertexSet();
	for(int i = 0; i < verts.size(); i++){
		transportStops.push((TransportStop *) verts[i]);
	}
	size_t counter = 0;
	while (counter < 10)
	{
		TransportStop *closest = transportStops.top();
		transportStops.pop();
		TransportEdge *edge1 = new TransportEdge(this, closest); // TODO delete
		TransportEdge *edge2 = new TransportEdge(closest, this); // TODO delete
		this->addEdge(edge1);
		closest->addEdge(edge2);
		++counter;
	}
	g->addVertex(this);
}

void TransportStop::userRemovefromGraph(Graph* g){
	for(int i = 0; i < this->getAdj().size(); i++){
		for(int j = 0; j < this->getAdj()[i]->getDst()->getAdj().size(); j++){
			if(this->getAdj()[i]->getDst()->getAdj()[j]->getDst() == this)
				this->getAdj()[i]->getDst()->removeEdge(j);
		}
	}
	g->removeLast();
}

double TransportStop::calcWaitingTime(Hour currentHour) const
{
	Hour nextHour(0, 0);
	bool found = false;
	for (size_t i = 0; i < schedule.size(); ++i)
	{
		if (schedule[i] > currentHour && schedule[i] < nextHour)
		{
			nextHour = schedule[i];
			found = true;
		}
	}
	if (found)
		return (nextHour - currentHour).getHourstamp();
	else
		return (schedule[0] - nextHour).getHourstamp();
}

void TransportStop::setParent(Edge *parent)
{
	TransportStop::setParent(parent);
	arrival = ((TransportStop *)parent->getSrc())->getArrivalTime() + (((TransportEdge *)parent)->calculateTime());
}
