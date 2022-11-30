#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const& i : adjList)
		{
			cout << " -> " << i;
		}
	}
	void printArray()
	{
		for (auto const& i : adjList)
		{
			cout << i << " ";
		}
	}
	int getSize()
	{
		return adjList.size();
	}
	int getElement(int idx)
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph
{
private:
	int V;
	vector<Adjacency> adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = vector<Adjacency>(V);
	}

	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}

	void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "Adjacency list of vertex " << v << "\n";
			adj[v].print();
		}
	}
	Adjacency BFS(int src)
	{
		vector<bool> visited(V, false);
		list<int> q;
		Adjacency arr;
		visited[src] = true;
		q.push_back(src);
		while (!q.empty())
		{
			int s = q.front();
			arr.push(s);
			q.pop_front();
			for (int i = 0; i < adj[s].getSize(); i++)
			{
				if (visited[adj[s].getElement(i)] == false)
				{
					visited[adj[s].getElement(i)] = true;
					q.push_back(adj[s].getElement(i));
				}
			}
		}
		return arr;
	}
	Adjacency DFS(int src)
	{
		vector<bool> visited(V, false);
		list<int> q;
		Adjacency arr;
		visited[src] = true;
		q.push_front(src);
		while (!q.empty())
		{
			src = q.front();
			q.pop_front();
			if (!visited[src])
			{
				arr.push(src);
				visited[src] = true;
			}
			for (int i = adj[src].getSize() - 1; i >= 0; i--)
			{
				if (!visited[adj[src].getElement(i)])
				{
					q.push_front(adj[src].getElement(i));
				}
			}
		}
		return arr;
	}
};
#endif // GRAPH_H
