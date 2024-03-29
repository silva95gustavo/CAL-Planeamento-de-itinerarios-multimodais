#include "AStar.h"


Path* astar(Graph* g, Vertex* ini, Vertex* f, GraphQueue<Vertex::AStarComp>* queue){
	vector<Vertex*> vertices = g->getVertexSet();
	queue->reset(vertices.size());
	for(size_t i= 0; i < vertices.size(); i++){
		vertices[i]->resetProcessed();
		vertices[i]->resetVisits();
		vertices[i]->setParent(NULL);
		vertices[i]->resetBestWeight();
	}
	ini->setBestWeight(0);
	ini->setParent(NULL);
	ini->incVisits();
	ini->calculateH(f);
	queue->push(ini);
	Vertex* current;
	while(queue->size() != 0)
	{
		current = queue->pop();
		current->incProcessed();
		if(current == f)
			break;
		vector<Edge*> adjs  = current->getAdj();
		for(size_t i = 0; i < adjs.size(); i++)
		{
			if(adjs[i]->getDst()->getProcessed() == 0)
			{
				double newWeight = current->getBestWeight() +adjs[i]->getWeight();
				if(newWeight < adjs[i]->getDst()->getBestWeight())
				{
					adjs[i]->getDst()->setBestWeight(newWeight);
					adjs[i]->getDst()->setParent(adjs[i]);
					if(adjs[i]->getDst()->getVisits() > 0)
					{
						queue->increase(adjs[i]->getDst());
					}
					else
					{
						adjs[i]->getDst()->calculateH(f);
						queue->push(adjs[i]->getDst());
					}
				}
			}
			adjs[i]->getDst()->incVisits();
		}
	}

	Path *p = new Path(f->getBestWeight());

	if(f != current) return p;

	int limit = g->getVertexSet().size();		// to stop from infinite loop
	while(current != ini && limit-- >= 0)
	{
		p->addEdgeBeginning(current->getParent());
		current = current->getParent()->getSrc();
	}
	return p;
}
Path* astar_list(Graph* g, Vertex* ini, Vertex* f){
	GraphQueue<Vertex::AStarComp>* queue = new GraphQueueList<Vertex::AStarComp>(g->getVertexSet().size());
	Path* p = astar(g, ini, f, queue);
	delete queue;
	return p;
}
Path* astar_fib(Graph* g, Vertex* ini, Vertex* f){
	GraphQueue<Vertex::AStarComp>* queue = new GraphQueueFib<Vertex::AStarComp>(g->getVertexSet().size());
	Path* p = astar(g, ini, f, queue);
	delete queue;
	return p;
}
