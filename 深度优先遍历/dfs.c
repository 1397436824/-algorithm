#include <dfs.h>


bool visited[MVNum];//访问标志数组，其初值为false



void DFS(Graph G,int v)
{//从v个顶点出发递归地深度优先遍历图
    cout<<v;visited[v]=true;//访问第v个顶点，并置访问标志数组相应分量值为true
    for(w=FirstAdjVex(G,v);w>0;w=NextAdjVex(G,v,w))
//依次检查v的所有邻接点w，FirstAdjVex(G,v)表示v第一个邻接点
//NextAdjVex(G,v,w)表示v相对于w的下一个邻接点，w>0表示有邻接点。
		if(!visited[w]) DFS(G,w);//对于v的尚未访问的邻接顶点w递归调用DFS
}













