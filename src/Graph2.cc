#include "Graph2.hh"

bool Graph2::loadInfo(char file_name[])
{
    FILE* fp;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("%s 文件打开失败！\n", file_name);
        return false;
    }

    std::pair<char[MAX_NAME_LEN], char[5]> info;
    int index;
    while (fscanf(fp, "%d %s %s", &index, info.first, info.second) != EOF) {
        _index_to_info[index] = info;
        printf("%d %s %s", index, info.first, info.second);
        printf(" readed\n");
    }
    fclose(fp);
    printf("person信息加载完成, 共读入%d个person数据\n", _index_to_info.size());
    return true;
}

bool Graph2::loadEdges(char file_name[])
{
    FILE* fp;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("%s 文件打开失败！\n", file_name);
        return false;
    }

    int edge;
    for (int i = 0; i < vertexNum(); ++i) {
        _adjacent_list.push_back(std::vector<int>());
        for (int j = 0; j < vertexNum(); ++j) {
            fscanf(fp, "%d", &edge);
            if (edge == 1) {
                _adjacent_list[_adjacent_list.size() - 1].push_back(j);
                ++_edgeNum;
            }
        }
    }
    fclose(fp);
    printf("edge信息加载完成\n");
    return true;
}

void Graph2::countInOutDegrees()
{
    for (int i = 0; i < vertexNum(); ++i) {  // init to zero
        _indegrees.push_back(0);
        _outdegrees.push_back(0);
    }

    for (int out_index = 0; out_index < vertexNum(); ++out_index)
        for (int in_index : _adjacent_list[out_index]) {
            ++_outdegrees[out_index];
            ++_indegrees[in_index];
        }
}

bool Graph2::eulerPathExist()
{
    countInOutDegrees();
    // start_nodes统计出度=入度+1的点数，end_nodes统计出度=入度-1的点数.
    int start_nodes = 0, end_nodes = 0;
    for (int i = 0; i < vertexNum(); ++i) {
        if (_outdegrees[i] - _indegrees[i] > 1 || _indegrees[i] - _outdegrees[i] > 1)
            return false;
        else if (_outdegrees[i] - _indegrees[i] == 1)
            ++start_nodes;
        else if (_indegrees[i] - _outdegrees[i] == 1)
            ++end_nodes;
    }
    // 两种情况存在欧拉路径。1.所有点入度等于出度（存在欧拉回路。2.入度=出度+1的点和出度=入度+1的点各一个。
    bool result = ((end_nodes == 0 && start_nodes == 0) || (end_nodes == 1 && start_nodes == 1));
    if (result)
        printf("euler path exists\n");
    else
        printf("euler path does not exist");
    return result;
}

int Graph2::findStartNode()
{
    if (_indegrees.size() == 0) {
        printf("indegrees and outdegrees array has not updated. error !\n");
        return -1;
    }

    int start_node = 0;
    for (int i = 0; i < vertexNum(); ++i) {
        if (_outdegrees[i] - _indegrees[i] == 1) {
            printf("euler path starts from: %d\n", i);
            return i;  // 存在欧拉路径,选择出度=入度+1结点起始。
        }
    }
    printf("euler ring starts from: %d\n", 0);
    return 0;  // 存在欧拉回路,随便选一个起点
}

void Graph2::dfsEulerPath(int start_node, std::vector<int>& path, std::vector<std::vector<int>>& visited)  //遍历边而不是结点
{
    for (int i = 0; i < _adjacent_list[start_node].size(); ++i) {
        if (visited[start_node][i] == 0) {
            int next_node = _adjacent_list[start_node][i];
            visited[start_node][i] = 1;
            // --_outdegrees[start_node];
            // printf("dfs starting from %d\n", next_node);
            dfsEulerPath(next_node, path, visited);
        }
    }
    path.push_back(start_node);
}