/*
	Exercise: Vertex Coloring
	1. Complete the basic greedy coloring program below.
	2. Analyze the running time of the program.
		In analyzing the running time of the program, the loop that assigns a color to each vertex iterates through the number of vertices or O(|V|). A function inside of the said loop, getAvailableColor,
		creates an availability array of size v and assigns all initial availablity to 1, which is also O(|V|). After creating the availability array, the function iterates through the linked list of the
		current vertex and marks the colors of the adjacent vertices as unavailable. There is a following loop that iterates through the availability array and gets the smallest available color, which is O(|V|).
		Therefore, the running time of the program is O(V^2), since there is a loop that runs |V| times inside of the loop that also runs |V| times in the greedy algorithm.
*/

#include<stdio.h>
#include<malloc.h>

typedef struct node{
	int x;
	struct node *next;
}graph;

graph **createAdjList(int *, int *);
void viewList(graph **, int);
int * graphColoring(graph **, int);
int getAvailableColor(graph **, int *, int, int);
void viewColor(int *, int);
void deleteGraph(graph **, int);

int main(){
	graph **g;
	int v, e, type;
	int *color;
	
	g = createAdjList(&v, &e);
	color = graphColoring(g, v);
	viewList(g, v);
	viewColor(color, v);
	
	free(color);
	deleteGraph(g, v);
}

graph **createAdjList(int *v, int *e){
    graph **g;

	//open graph.in file and read contents
	FILE *fp;
	fp = fopen("graph.in", "r");

	if(fp == NULL){
		printf("Error opening graph.in\n");
		return g;
	}

    /*insert code here for creating an adjacency list*/
    // Read v and e
    int vertices = *v;
    int edges = *e;

    fscanf(fp, "%d", &vertices);
    fscanf(fp, "%d", &edges);

	//assign to the values of v an e
	*v = vertices;
	*e = edges;

    g = (graph**)malloc((vertices) * sizeof(graph*));

	//initialize all vertices in the graph to be null
	for(int i = 0; i < vertices; i++){
		g[i] = NULL;
	}

	for(int i = 0; i < edges; i++){
		graph* pre; 
        graph* post;
        //pointer = *pre;
        int val1, val2;
        // printf("inside loop");
        fscanf(fp, "%d %d\n", &val1, &val2);

        pre = malloc(sizeof(graph));
        pre->x = val1;
        pre->next = NULL;

        post = malloc(sizeof(graph));
        post->x = val2;
        post->next = NULL;

        if(g[val1] == NULL){
            // if the given vertex doesn't have a set of vertices connected to it yet, make one
            g[val1] = post;
        }else{ //otherwise, append to the tail
            graph* temp = g[val1];
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = post;
            // traverse through linked list, pag umabot sa dulo, add
            
        }
        //does the same thing, except it's done for the 2nd value
        if(g[val2] == NULL){
            g[val2] = pre;
        }else{ // traverse through the 2nd vertex's linked list, append to tail
            graph* temp = g[val2];
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = pre;
            // traverse through linked list, pag umabot sa dulo, add
        }
	}

	//close file
	fclose(fp);
    return g;
}

void viewList(graph **g, int v){
	int i;
	graph *p;
	
	for(i = 0; i < v; i++){
		p = g[i];
		printf("%d: ", i);
		//traverse the list connected to vertex i
		while(p != NULL){
			printf("%3d", p->x);
			p = p->next;
		}
		printf("\n");
	}
}

int * graphColoring(graph **g, int v){
	int *color, availCol, i;
	
	//colors are represented as integers starting from 0
	color = (int *)malloc(sizeof(int)*v);
	for(i = 0; i < v; i++)
		color[i] = -1;
	
	color[0] = 0;	//assign first vertex with the first color
	for(i = 1; i < v; i++){
		availCol = getAvailableColor(g, color, v, i);
		color[i] = availCol;
	}
	return color;
}

int getAvailableColor(graph **g, int *color, int v, int curr){
	graph *p;
	int *available, i, availCol;

	//printf("I am getting the available color for vertex %d\n", curr);
	
	//keeps track of the colors used on any previously colored vertices adjacent to it
	available = (int *)malloc(sizeof(int)*(v));
	for(i = 0; i < v; i++)
		available[i] = 1;
	
	/*Insert code here for marking the colors that have been used 
	on any previously colored vertices adjacent to it.*/

	//mark the colors that have been used on the adjacent vertices

	p = g[curr]; // assign p to the head of the linked list of the current vertex
	//traverse the linked list. mark the color of the adjacent vertices as unavailable
	while(p != NULL){
		if(color[p->x] != -1){
			available[color[p->x]] = 0;
		}
		p = p->next;
	}
	
	for(i = 0; i < v; i++){				//get the smallest color that is available
		if(available[i] == 1){
			availCol = i;
			break;
		}
	}
	
	free(available);
	return availCol;
}

void viewColor(int *color, int v){
	int i;
	
	for(i = 0; i < v; i++){
		printf("Vertex %d -> Color %d\n", i, color[i]);
	}
}

void deleteGraph(graph **g, int v){
	int i;
	graph *p;
	for(i = 0; i < v; i++){
		while(g[i] != NULL){
			p = g[i];
			g[i] = g[i]->next;
			free(p);
		}
	}
	free(g);
}