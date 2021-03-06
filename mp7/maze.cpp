#include <vector>
#include "dsets.h"
#include "maze.h"
#include <iostream>
#include <unordered_map>
#include <queue>
SquareMaze::SquareMaze(){}
void SquareMaze::makeMaze (int width,int height) {
	width_=width;
	height_=height;
	int sets=width*height;
	int last=width*height-1;
	forest.myarray.clear();
	forest.addelements(width*height);
//	int square=0;
	walls= vector <vector <int>>();
	//walls={};
	/*for(int j=0;j<walls.size();j++){
		delete walls[j];
	}*/
	//visited=vector<int>();
	for(int i=0;i<width*height;i++){///wouldn't it be faster to do a O(1) intialization dude??
		vector<int> temp {1,1};
		temp.push_back(1);
		temp.push_back(1);
		walls.push_back(temp);
		//visited.push_back(false);
		//dist.push_back(-inf);
	}
	while(sets!=1){
		int square=rand()%(width*height);
		int dir=rand()%2;//0 means right, 1 means down
		if(walls[square][dir]==0) dir=1-dir;//that wall was already removed, try other one
		///if(walls[square][dir]==0) {} //both walls were already removed
		if(walls[square][dir]==1){//remove this wall
			if(dir==0&&(square%width!=width-1)){//right and not a right sided square
				if(forest.find(square)!=forest.find(square+1)){
					//forest.myarray[square+1]=square;
					forest.setunion(square,square+1);
					walls[square][dir]=0;//no wall here
					sets--;
				}
			}
			if(dir==1&&(square<width*(height-1))){//bottom and not a bottom sided square
				if(forest.find(square)!=forest.find(square+width)){
					//forest.myarray[square+width]=square;
					forest.setunion(square,square+width);
					walls[square][dir]=0;//no wall here
					sets--;
				}
			}
		}
	}

/*	for(int i=0;i<width*heigh;i++){
		neighbors[i]=new vector<int>;
		if(i-1>=0){
		neighbors[i].push(i-1);
		}
		if(i-width>=0) neighbors[i].push(i-row);
		if(i+1<width*height) neighbors[i].push(i+1);
		if(i+widht<width*height) neighbors[i].push(i+width);

	}

	queue <int> q;
	q.push(square);
	//graph.setVertexLabel
	while(!q.empty()){
		int s=q.front();
		q.pop();
		vector <int> nv= neighbors[s];
		int j=rand()%(nv.size());	
		//for(size_t j=0;j<nv.size();j++){
		int others=nv[j];
		in
		if(forest.find(s)==forest.find(others)){
			
		}
			if(graph.getVertexLabel(w)=="UNEXPLORED"){
				//graph.setEdgeLabel(v,w,"DISCOVERY");
				graph.setVertexLabel(w,"VISITED");
				q.push(w);
				Edge thisedge=graph.getEdge(v,w);
				m[w]=v;
			}

	
		//}

	}

*/
}

bool SquareMaze::canTravel (int x, int y, int dir) const {
/*
    dir = 0 represents a rightward step (+1 to the x coordinate)
    dir = 1 represents a downward step (+1 to the y coordinate)
    dir = 2 represents a leftward step (-1 to the x coordinate)
    dir = 3 represents an upward step (-1 to the y coordinate)
*///cant't go off or go through wall
if(x<0||x>=width_||y<0||y>=height_) return false;
if(dir==0&&x!=(width_-1)&&walls[x+y*width_][0]==0) return true;
if(dir==1&&y!=(height_-1)&&walls[x+y*width_][1]==0) return true;
if(dir==2&&x!=0){if(walls[x+y*width_-1][0]==0) return true;}
if(dir==3&&y!=0){if(walls[x+(y-1)*width_][1]==0) return true;}
return false;
}
void SquareMaze::setWall (int x, int y, int dir, bool exists){
//0 right, 1 down
	if(x<0||x>=width_||y<0||y>=height_) return;
	if(dir==0&&x!=(width_-1)){
		if(exists)walls[x+y*width_][0]=1;
		else walls[x+y*width_][0]=0;
	}
	if(dir==1&&y!=(height_-1)){
		if(exists)walls[x+y*width_][1]=1;
		else walls[x+y*width_][1]=0;
	} 
}

vector< int > SquareMaze::solveMaze (){


/*Solves this SquareMaze.

For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.

Select the square in the bottom row with the largest distance from the origin as the destination of the maze. solveMaze() returns the winning path from the origin to the destination as a vector of integers, where each integer represents the direction of a step, using the same encoding as in canTravel().

If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.

Hint: this function should run in time linear in the number of cells in the maze.

Returns
    a vector of directions taken to solve the maze */

	//vector<int> ret= vector<int>();
	int dest=width_*(height_-1); //the leftest square on bottom row
	int curr=0;
	queue <int> q;
	q.push(curr);
	//vector<int> temp=vector<int>();
	vector <bool> visited;
	visited.resize(width_*height_);

	unordered_map<int,int> parent;
	parent[0]=0;
	while(!q.empty()){
	
		//manhattan heuristic???
		/*
		function heuristic(node) =
		    dx = abs(node.x - goal.x)
		    dy = abs(node.y - goal.y)
		    return D * (dx + dy)
		*/
		curr=q.front();
		q.pop();
		visited[curr]=true;
		int x=curr%width_;
		int y=curr/width_;
		//vector<int> vdir={};
		if(canTravel(x,y,0)){//right direction
			if(!visited[curr+1]){
				q.push(curr+1);
				visited[curr+1]=true;
				parent[curr+1]=curr;
			}
		}
		if(canTravel(x,y,1)){//down direction
			if(!visited[x+(y+1)*width_]){
				q.push(x+(y+1)*width_);
				visited[x+(y+1)*width_]=true;
				parent[x+(y+1)*width_]=curr;
			}
		}	
		if(canTravel(x,y,2)){//left direction
			if(!visited[curr-1]){
				q.push(curr-1);
				visited[curr-1]=true;
				parent[curr-1]=curr;
			}
		}
		if(canTravel(x,y,3)){//up direction
			if(!visited[x+(y-1)*width_]){
				q.push(x+(y-1)*width_);
				parent[x+(y-1)*width_]=curr;
				visited[x+(y-1)*width_]=true;
			}
		}
	
	}

vector<vector<int>> paths={};
paths.resize(width_);
int endcell=0;
for(int i=0;i<width_;i++){
	vector<int> temp=vector<int>();
	int goback=dest+i;//do dir backwards
	while(goback!=0){
		int xend=goback%width_;
		int yend=goback/width_;
		int xnew=parent[goback]%width_;
		int ynew=parent[goback]/width_;
		if(xnew-xend==1){//right
			temp.push_back(2);	
		}
		if(xnew-xend==-1){//left
			temp.push_back(0);	
		}
		if(ynew-yend==1){//down
			temp.push_back(3);	
		}
		if(ynew-yend==-1){//up
			temp.push_back(1);	
		}



		goback=parent[goback];
	}
paths[i]=temp;
if(temp.size()>paths[endcell].size()) endcell=i;	
}
vector<int> ret=paths[endcell];
 std::reverse(ret.begin(),ret.end()); //decided to only reverse the winner
//solution=ret;
int end=endcell+dest;
	return ret;
}

/*    dir = 0 represents a rightward step (+1 to the x coordinate)
    dir = 1 represents a downward step (+1 to the y coordinate)
    dir = 2 represents a leftward step (-1 to the x coordinate)
    dir = 3 represents an upward step (-1 to the y coordinate)*/
/*
void GraphTools::findMST(Graph& graph)
{
vector<Vertex> vertices = graph.getVertices();
	DisjointSets vertexSet;
	vertexSet.addelements(vertices.size());
	vector<Edge> edges = graph.getEdges();
	std::sort(edges.begin(), edges.end());
	for(unsigned i = 0; i < edges.size(); i++)	{
		Vertex a = edges[i].source;
		Vertex b = edges[i].dest;
		if(vertexSet.find(a) != vertexSet.find(b))	{
			vertexSet.setunion(a, b);
			graph.setEdgeLabel(a, b, "MST");
		}
	}
} 
*/

 
PNG * SquareMaze::drawMaze () const{


/*Draws the maze without the solution.

First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). where height and width were the arguments to makeMaze. Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y). If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.

Returns
    a PNG of the unsolved SquareMaze 
*/
PNG * image=new PNG(width_*10+1,height_*10+1);
/*for(int i=0;i<width_*10+1;i++){
	for(int j=0;j<height_*10+1;j++){
		HSLAPixel *p=image->getPixel(i,j);
		if(i==0||(j==0&&i>=10)){
		p->h=0;
		}
		if(j==0&&(i>=1&&i<=9)){
		p->h=360;//is it white or set? idk
		}
		if(
	}
}*///dont wanna go through every pixel, just intialization
	cs225::HSLAPixel *p;
	for(int i=0;i<height_*10+1;i++){//left column
	p=image->getPixel(0,i);
	p->l=0;
	}
	for(int j=10;j<width_*10+1;j++){//left column
	p=image->getPixel(j,0);
	p->l=0;
	}
	for(int l=0;l<width_*height_;l++){
		int x=l%width_;
		int y=l/width_;
		if(walls[l][0]==1){//right wall exists
			for(int k=0;k<=10;k++){
				p=image->getPixel((x+1)*10,y*10+k);
				p->l=0;
			}
		}
		if(walls[l][1]==1){//bottom wall exists
			for(int k=0;k<=10;k++){
				p=image->getPixel(x*10+k, (y+1)*10);
				p->l=0;
			}
		}
	}
//for(
//solution=vector<int>();  
return image;





//PNG fake=PNG();
/*PNG *faker=NULL;//= & PNG();
return faker;*/
}

 
PNG * SquareMaze::drawMazeWithSolution (){

/*This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). Then if the second step is right, color pixels (5,15) through (15,15) red. Then if the third step is up, color pixels (15,15) through (15,5) red. Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.

Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.*/

/*    dir = 0 represents a rightward step (+1 to the x coordinate)
    dir = 1 represents a downward step (+1 to the y coordinate)
    dir = 2 represents a leftward step (-1 to the x coordinate)
    dir = 3 represents an upward step (-1 to the y coordinate)*/
	//solveMaze();
	PNG *ret=drawMaze();
	vector<int>solution=solveMaze();
	cs225::HSLAPixel *p=ret->getPixel(5,5);
	p->h=0;
	p->s=1;
	p->l=0.5;
	p->a=1;
	int x=5;
	int y=5;
	for(size_t i=0;i<solution.size();i++){
		int dir=solution[i];
		if(dir==0){
			for(int j=0;j<=10;j++){
				p=ret->getPixel(x+j,y);
				p->h=0;
				p->s=1;
				p->l=0.5;
				p->a=1;		
			}
			x=x+10;
		}
		if(dir==1){
			for(int j=0;j<=10;j++){
				p=ret->getPixel(x,y+j);
				p->h=0;
				p->s=1;
				p->l=0.5;
				p->a=1;		
			}
			y=y+10;
		}
		if(dir==2){
			for(int j=0;j<=10;j++){
				p=ret->getPixel(x-j,y);
				p->h=0;
				p->s=1;
				p->l=0.5;
				p->a=1;		
			}
			x=x-10;
		}
		if(dir==3){
			for(int j=0;j<=10;j++){
				p=ret->getPixel(x,y-j);
				p->h=0;
				p->s=1;
				p->l=0.5;
				p->a=1;		
			}
			y=y-10;
		}
	}
/*Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.*/
//walls[end][1]=0;
int endx=x/10;
int endy=height_-1;
for(int k=1;k<=9;k++){
p=ret->getPixel(endx*10+k, (endy+1)*10);
				p->h=0;
				p->s=0;
				p->l=1.0;
				p->a=1.0;	
}
	return ret;
}
