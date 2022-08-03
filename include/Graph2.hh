#ifndef CPP_PROGRAM_ASSIGNMENT2_INCLUDE_GRAPH2_HH_
#define CPP_PROGRAM_ASSIGNMENT2_INCLUDE_GRAPH2_HH_

#include <fstream>
#include <map>
#include <vector>

#define MAX_NAME_LEN 20

// 有向图存在欧拉路径的条件：
// 1.所有的点连通。
// 2.
// (1)所有的点出度等于入度
// (2)一个点满足出度 = 入度 + 1,一个点满足入度 = 出度 + 1, 其余点满足出度 = 入度。
class Graph2
{
   public:
    Graph2() { _edgeNum = 0; }
    ~Graph2() = default;

    int vertexNum() { return _index_to_info.size(); }

    int edgeNum() { return _edgeNum; }

    bool loadInfo(char file_name[]);

    bool loadEdges(char file_name[]);

    bool eulerPathExist();

    void findEulerPath(std::vector<int>& path)
    {
        if (!eulerPathExist())
            printf("no euler path!\n");
        std::vector<std::vector<int>> visited = _adjacent_list;
        for (int out_index = 0; out_index < vertexNum(); ++out_index)
            for (int in_index = 0; in_index < visited[out_index].size(); ++in_index)
                visited[out_index][in_index] = 0;
        dfsEulerPath(findStartNode(), path, visited);
    }

    void showGraph()
    {
        for (int i = 0; i < vertexNum(); ++i) {
            printf("[%d] --> ", i);
            for (int vertex : _adjacent_list[i])
                printf(" %d -->", vertex);
            printf("\n");
        }
    }

    void showPath(std::vector<int>& path)
    {
        if (path.size() == edgeNum() + 1) {
            for (int i = 0; i < path.size() - 1; ++i)
                printf("%d --> ", path[i]);
            printf("%d\n", path[path.size() - 1]);
            for (int i = 0; i < path.size() - 1; ++i)
                printf("%s --> ", _index_to_info[path[i]].first.c_str());
            printf("%s\n", _index_to_info[path[path.size() - 1]].first.c_str());
        } else
            printf("no euler path or euler ring\n");
    }

   private:
    // count indegrees and outdegrees, saved in class members;
    void countInOutDegrees();

    // find starting node among the two vertices;
    int findStartNode();

    // Depth-first search
    void dfsEulerPath(int start_node, std::vector<int>& path, std::vector<std::vector<int>>& visited);

    std::map<int, std::pair<std::string, std::string>> _index_to_info;
    std::vector<std::vector<int>> _adjacent_list;
    std::vector<int> _indegrees;
    std::vector<int> _outdegrees;

    int _edgeNum;
};

#endif