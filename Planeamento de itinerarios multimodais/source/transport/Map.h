/*
 * Map.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_MAP_H_
#define SOURCE_MAP_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidxml/rapidxml.hpp"
#include "../include/rapidxml/rapidxml_utils.hpp"
#include "../include/rapidxml/rapidxml_print.hpp"
#include "BusStop.h"
#include "BusEdge.h"
#include "BusRoute.h"
#include "../graph/Vertex.h"
#include "MetroStop.h"
#include "MetroRoute.h"
#include "../graph/Graph.h"

/**
 * @brief Abstraction to the real "world" map, able to convert it to a Graph
 */
class Map {
private:
	std::vector<BusRoute> busRoutes;
	std::vector<MetroRoute> metroRoutes;
public:
	/**
	 * @brief map construtor
	 */
	Map();

	class Loader {
	private:
		static const std::string dataFolder;
		static const std::string BusEdgesFolder;
		static const std::string busStopsFolder;
		static const std::string timetablesFolder;
		static const std::string connectingEdgesPreProcessingFile;
		std::vector<std::string> getFilesInFolder(const std::string &folder) const;
		void parseJsonFile(const std::string file, rapidjson::Document &d) const;
		void parseXMLFile(rapidxml::file<> &file, rapidxml::xml_document<> &d) const;
		void findBusInfoFromFileName(const string &fileName, std::string &code, bool &direction) const;
		std::vector<BusStop *> loadBusStops(const rapidjson::Document &d, const std::string& route_code) const;
		std::vector<BusEdge> loadBusEdges(const rapidjson::Document &d, vector<BusStop *> &busStops) const;
		void loadBusRoutes(std::vector<BusRoute> &busRoutes) const;
		void loadSchedule(const BusRoute &busRoute) const;
		std::vector<std::pair<MetroStop *, std::string> > loadMetroStopNodes(rapidjson::Document &d) const;
		MetroStop *loadMetroStop(MetroStop &metroStop);
		std::vector<MetroStop> loadMetroStops(rapidjson::Document &d) const;
		MetroStop *findClosestMetroStop(vector<MetroStop> &metroStops, const string &metroStopCode) const;
		void loadMetroRoutes(std::vector<MetroRoute> &metroRoutes) const;
		Hour generateRandomHour() const;
		void generateRandomTransportSchedule(unsigned dailyFrequency, TransportRoute *transportRoute) const;
		void createConnectingEdges(vector<BusRoute> &busRoutes, vector<MetroRoute> &metroRoutes) const;
		void connectToClosests(vector<BusRoute> &busRoutes, vector<MetroRoute> &metroRoutes, TransportStop *transportStop) const;
		void saveConnectingEdges(const vector<BusRoute> &busRoutes, const vector<MetroRoute> &metroRoutes) const;
		void loadConnectingEdges(const vector<BusRoute> &busRoutes, const vector<MetroRoute> &metroRoutes) const;
		unsigned levenshteinDistance(const string &s1, const string &s2) const;
	public:
		void load(Map &map);

		class InvalidInputException {
			std::string info;
		public:
			InvalidInputException(const string &info): info(info) {}
			const string &getInfo() { return info; }
		};

	};
	friend class Loader;
	const std::vector<BusRoute>& getBusRoutes() const {return busRoutes;}
	const std::vector<BusStop *>& getBusStops() const;
	Graph generateGraph() const;
};

#endif /* SOURCE_MAP_H_ */
