#ifndef NECKLACE_SIMPLEGRAPH_H
#define NECKLACE_SIMPLEGRAPH_H


class SimpleGraph {
    private:
        int _vertices;
        int _edges;

    public:
        SimpleGraph(int vertices, int edges): _vertices(vertices), _edges(edges) { }

        int getVertices() const ;
        int getEdges() const ;
};


#endif //NECKLACE_SIMPLEGRAPH_H
