// project 4 hamza al shaer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define INFINITY 9999//infinity used
int max_city ;
// Queue implementation using arrays
int queue[100];
int front = -1, rear = -1;
char Verticies[15][15];
// Queue implementation using arrays
int countVerticies(char Verticies[][15],int size)
{   FILE *fin = fopen("cities.txt","r");
    int count = 0 ;
    char start [30];
    char end [30];
    int cost ;

    while(fscanf(fin,"%s %s %d",&start,&end,&cost) != EOF)
    {
        if(count == 0)
        {   // if just one city store ,, copy city without compare and ++ so it is first city
            strcpy(Verticies[0],start);
            count++;
        }
        else
        {
            char temp[30];
            int isUnique = 1;//flag to cheack compare
            // copy city name and store temp array to compare with all vartices in array
            strcpy(temp,start);
            for(int i = 0 ; i < count; i++  )
            {
                if(strcmp(temp,Verticies[i])== 0) // if temp array equle with any index data not happend anything
                {
                    isUnique = 0 ;//if it occured once then it shouldn't be added
                }
            }
            // if flag 1 such that no city equle so store
            if(isUnique)
            {
                strcpy(Verticies[count],temp);//add to vertices list
                count++;
            }
        }
    }
    fclose(fin);
    return count;//number of unique vertices
}
// to compare and add edage in graph
void add_Edge_graph(int graph [][max_city],char city1[],char city2[],int cost){
    int index1=-1;
    int index2=-1;
    for (int i = 0; i < max_city; ++i) {
        if (strcmp(Verticies[i], city1) == 0)
            index1 = i;
        if (strcmp(Verticies[i], city2) == 0)
            index2 = i;

        if (index1 != -1 && index2 != -1){
            graph[index1][index2] = cost;
            break;
        }
    }
}
// read data from the file and store in graph
void readFile(int graph [][max_city])
{
    FILE *fin = fopen("cities.txt","r");
    int counter = 0;
    char from[30];
    char to[30];
    int cost;
    while(fscanf(fin,"%s %s %d",&from,&to,&cost) != EOF)
    {
        add_Edge_graph(graph,from,to,cost);
    }
    fclose(fin);
}
void printGraph(int graph[max_city][max_city]) {
    printf("Graph Matrix:\n");
    for (int i = 0; i < max_city; i++) {
        for (int j = 0; j < max_city; j++) {
            printf("%d  ", graph[i][j]);
        }
        printf("\n");
    }
    printf(" \n");
}
// ------------------------- up done read data -----------------------------------------------------
// Function to find the vertex with the minimum distance value ,, less vlue of dist in array
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX;
    int less_index;
    for (int i = 0; i < max_city; i++) {
        if (visited[i] == false && dist[i] <= min) {
            // sote in min fisrt dist aftter this compere whith anthor dist
            min = dist[i];
            less_index = i;
        }
    }
    // return index of less distance
    return less_index;
}
int generateIndex(char city[20]) //each verticii is given an index according to its order in unique array
{
    for(int j = 0 ; j < max_city; j++)
    {
        if(strcmp(city,Verticies[j])==0)
        {
            return j;
        }
    }
    return -1;
}
// Function to print the shortest path from the source to the destination
void printPath_dijksrt( int cost [30],int parent_of_city[], int vertex ) {
    if (parent_of_city[vertex] == -1) {
        printf("-(Distance: %d)- %s  ",cost[vertex],Verticies[ vertex]);
        return;
    }
    printPath_dijksrt(cost,parent_of_city, parent_of_city[vertex]);
    printf("-(Distance: %d)- %s  ",cost[vertex],Verticies[ vertex]);
}
// Function to perform Dijkstra's algorithm
void Dijkstra(int graph[max_city][max_city], int source, int destination ,bool visited_city[max_city] , int parent_of_city[max_city] ,int short_distance[max_city],int cost [30]) {
    printf("\n");
    // Initialize for distance and visited  and parent arrays
    for (int j = 0; j < max_city; j++) {
        parent_of_city[j] = -1;
        short_distance[j] = INT_MAX;
        cost [j]=0;
        visited_city[j] = false;
    }
    // Distance from source to itself is  0
    short_distance[source] = 0;
    // Find the shortest path for all cities
    for (int k = 0; k < max_city - 1; k++) {
        int m = minDistance(short_distance, visited_city);
        visited_city[m] = true;

        for (int i = 0; i < max_city; i++) {
            if (!visited_city[i] && graph[m][i] != 0 && short_distance[m] != INT_MAX && short_distance[m] + graph[m][i] < short_distance[i]) {
                short_distance[i] = short_distance[m] + graph[m][i];
                parent_of_city[i] = m;
                cost[i]=graph[m][i];
            }
        }
    }
    // Print the shortest path and distance from source to destination
    printPath_dijksrt(cost,parent_of_city, destination);
    printf(" \n Distance: %dkm \n", short_distance[destination]);
}
//-------------------------------------up dijstra method---------------------------------------------------------
// Function to add an element to the queue
void enqueue(int value) {
    if (rear == max_city - 1) {
        printf("");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = value;
}
// Function to remove an element from the queue
int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    int value = queue[front];
    front++;
    return value;
}

// Function to check if the queue is empty
bool isQueueEmpty() {
    return (front == -1 || front > rear);
}
// Function to print the shortest path from the source to the destination
void printPath_BFS( int vertex,int parent[]) {
    if (parent[vertex] == -1) {
        printf("%s -> ",Verticies[ vertex]);
        return;
    }
    printPath_BFS(parent[vertex],parent);
    printf("%s -> ",Verticies[vertex]);
}
// Function to perform Breadth First Search (BFS)
void BFS(int graph[max_city][max_city],int source, int destination,bool visited[max_city],int parent[max_city]) {
    printf("\n");
    // Array to track visited vertices set fales
    for(int i = 0 ; i<max_city ;i++)
        visited[i]=false;
    // Initialize parent array set initialization
    for (int i = 0; i < max_city; i++) {
        parent[i] = -1;
    }
    // Mark the source vertex as visited and enqueue it
    visited[source] = true;
    enqueue(source);
    while (!isQueueEmpty()) {
        int currentVertex = dequeue();

        // If the destination vertex is found, break the loop
        if (currentVertex == destination) {
            break;
        }
        // Explore all the adjacent vertices of the current vertex
        for (int j = 0; j < max_city; j++) {
            if (graph[currentVertex][j] && !visited[j]) {
                visited[j] = true;
                enqueue(j);
                parent[j] = currentVertex;
            }
        }
    }
    // Check if the destination vertex is reachable from the source vertex
    if (!visited[destination]) {
        printf("Destination vertex is not reachable from the source vertex.\n");
        return;
    }
    printPath_BFS(destination,parent);
    printf("\n\n");
}
//-------------------------------------------up BFC---------------------------------------------------------------------
// Functions to print the shortest path from the source to the destination in file
void printPaths_in_file_Dijkstra(int parent[], int vertex, FILE*fout , int cost[]) {
    if (parent[vertex] == -1) {
        fprintf(fout,"%s -(Distance: %d)- ",Verticies[ vertex],cost[vertex]);
        return;
    }
    printPaths_in_file_Dijkstra(parent, parent[vertex],fout,cost);
    fprintf(fout,"%s -(Distance: %d)- ",Verticies[ vertex],cost[vertex]);

}
void printPaths_in_file_BFS(int parent[], int vertex , FILE*fout) {
    if (parent[vertex] == -1) {
        fprintf(fout,"%s -> ",Verticies[ vertex]);
        return;
    }
    printPaths_in_file_BFS(parent, parent[vertex],fout);
    fprintf(fout,"%s -> ",Verticies[ vertex]);
}
//----------------------------------------up print on file--------------------------------------------------------------
int main() {
    max_city =countVerticies(Verticies,20);
    int cost [30];
    bool visited_city[max_city];  // Array to track visited cities
    int parent_of_city[max_city];  // Array to store the parent of each city
    int short_distance[max_city];  // Array to store the shortest distances
    int graph [max_city][max_city];
    int cheak =0 ;
    char source_city[30];
    char destination_city[30];
    // to Zeroing all matrix
    for(int i = 0; i < max_city; i++)
    {
        //initiate Graph values at 0
        for(int j = 0 ; j < max_city ; j++)
        {
            graph[i][j]= 0;//initiates the array
        }
    }
    while (cheak!=4){
        printf("Select process from 1-4 .. : \n");
        printf("1. Load cities  ... \n ");
        printf("2. Enter source ... \n");
        printf("3. Enter destination  .... \n");
        printf("4. Exit ... \n");
        scanf("%d",&cheak);
        switch (cheak) {
            case 1:
                readFile(graph);
                // printGraph(graph);  to test only
                break;
            case 2:
                printf("please enter source city:: \n"); // start city
                scanf("%s",&source_city);
                printf("\n");
                break;
            case 3:
                printf("please enter the specific destination : \n");
                scanf("%s",&destination_city);
                printf("shortest path from %s to %s : \n",source_city,destination_city);
                Dijkstra(graph, generateIndex(source_city), generateIndex(destination_city),visited_city,parent_of_city,short_distance,cost);
                BFS(graph, generateIndex(source_city), generateIndex(destination_city),visited_city,parent_of_city);
                break;
            case 4:
                break;
            default:
                printf("not a valid option ! \n");
                break;
        }
    }
    FILE* fout = fopen("shortest_distance.txt","w");
    fprintf(fout,"Dijkstra result : \n");
    fprintf(fout,"shortest path from %s to %s : \n",source_city,destination_city);
    printPaths_in_file_Dijkstra(parent_of_city,generateIndex(destination_city),fout,cost);
    fprintf(fout,"\n");
    fprintf(fout,"Distance: %dkm \n", short_distance[generateIndex(destination_city)]);
    fprintf(fout,"BFS result : \n");
    fprintf(fout,"shortest path from %s to %s : \n",source_city,destination_city);
    printPaths_in_file_BFS(parent_of_city,generateIndex(destination_city),fout);
    fclose(fout);
    printf("exist done");
    return 0;
}