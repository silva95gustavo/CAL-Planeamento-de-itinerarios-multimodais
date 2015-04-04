/*
 * TransportEdge.h
 *
 *  Created on: 03/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_TRANSPORTEDGE_H_
#define SOURCE_TRANSPORTEDGE_H_

#include "Edge.h"
#include "Coordinates.h"
#include <vector>

class TransportEdge: public Edge {
protected:
	std::vector<Coordinates> line;
public:
	TransportEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line);
	void addPoint(const Coordinates &coords);
	double getDist() const { return storedWeight; }
	const std::vector<Coordinates> &getLine() const;
	virtual ~TransportEdge() { }
};

#endif /* SOURCE_TRANSPORTEDGE_H_ */