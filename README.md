# GraphAlgorithm-EulerPath
Finding Euler Path or Euler Ring in a directed graph

创建一个Person类，包含名字，出生年份信息，在**people.txt**文件中输入几个人，如下示例

0 Bassel 1993

1 Sawsan 1997

2 Thuraya 1960

3 abes 2007

4 Farnes 2009

5 Baheye 2011

6 sam 2021

这几个人之间如A认识B，B不认识A，或者AB相互认识，或者AB相互不认识。认识关系可以由矩阵表示，写在文件**relationship.txt**中，如下示例

0 1 0 0 0 0 1

0 0 1 0 0 0 0

1 0 0 1 0 0 0

0 0 0 0 1 0 0

0 0 1 0 0 1 0

1 0 0 0 0 0 0

0 0 0 0 1 0 0

由此构成一个如下的有向图，请判断该图是否存在欧拉路径（一笔经过图中所有边）和欧拉回路（欧拉路径是回路），如存在路径按顺序打印具体点的信息，即人的名字，年龄信息,如不存在输出No Eular Path。

[![Euler2](https://media.geeksforgeeks.org/wp-content/uploads/Euler2.jpg)]

**输出欧拉路径** : Bassel-> sam-> Farnes -> Baheye -> Bassel -> Sawsan -> Thuraya->abes-> Farnes-> Thuraya-> Bassel

求解思路：

有向图存在欧拉路径的条件：

1.所有的点连通。

2.满足二者之一

（1）所有的点出度等于入度

（2）一个点满足出度 = 入度 + 1, 一个点满足入度 = 出度 + 1, 其余点满足出度 = 入度。
