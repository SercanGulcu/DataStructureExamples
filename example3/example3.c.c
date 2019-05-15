#include<stdio.h>
#include<stdlib.h>
struct nodeFB
{
int id;
int age;
struct nodeFB *next;
}typedef  nodeFB;

struct nodeGS
{
int id;
struct nodeGS *next;
}typedef  nodeGS;

struct nodeBoth
{
	int id;
	int age;
	struct nodeBoth *next;
}typedef nodeBoth;

nodeFB * add_fb(nodeFB * fans,int id_fb,int age_fb );
nodeGS * add_gs(nodeGS * fans,int id_gs );
nodeBoth * add_both(nodeBoth *fans,nodeFB *fb_fans, nodeGS *gs_fans);
void printFB(nodeFB *fans);
void printGS(nodeGS *fans);
void printAll(nodeBoth *fans);
int main()
{
	nodeFB *fb=NULL;
	int id, age;
    scanf("%d%d", &id, &age);
    while (id != -1 && age != -1)
    {
        fb = add_fb(fb, id, age);
        scanf("%d%d", &id, &age);
    }
    
    nodeGS *gs=NULL;
    scanf("%d", &id);
    while (id != -1 )
    {
        gs = add_gs(gs, id);
        scanf("%d", &id);
    }
    nodeBoth *both=NULL;
    both=add_both(both,fb,gs);
    
    
	printFB(fb);
	printf("\n");
	printGS(gs);
	printf("\n");
	printAll(both);
}

nodeFB * add_fb(nodeFB * fans,int id_fb,int age_fb ){
	nodeFB *newnode,*ptr;
	
		if(fans==NULL){
		fans = (nodeFB *)malloc(sizeof(nodeFB));
		fans->id = id_fb;
        fans->age = age_fb;
        fans->next = NULL;
         return fans;
		}
		if(fans->id > id_fb){
		newnode = (nodeFB *)malloc(sizeof(nodeFB));
        newnode->id = id_fb;
        newnode->age = age_fb;
        newnode->next =fans;
		 return newnode;
		}
		
		ptr=fans;
		while(ptr->next!=NULL && ptr->next->id <id_fb){
			ptr=ptr->next;
		}
		newnode=(nodeFB*)malloc(sizeof(nodeFB));
		newnode->id=id_fb;
		newnode->age=age_fb;
		newnode->next=ptr->next;
		ptr->next=newnode;
		return fans;
}

void printFB(nodeFB *fans){

	while(fans!=NULL){
		printf("Id=%d	Age:%d\n",fans->id,fans->age);
		fans=fans->next;
	}
}
nodeGS * add_gs(nodeGS * fans,int id_gs ){
	nodeGS *newnode,*ptr;
	
		if(fans==NULL){
		fans = (nodeGS *)malloc(sizeof(nodeGS));
		fans->id = id_gs;
        fans->next = NULL;
         return fans;
		}
		if(fans->id < id_gs){
		newnode = (nodeGS *)malloc(sizeof(nodeGS));
        newnode->id = id_gs;
        newnode->next =fans;
		 return newnode;
		}
		
		ptr=fans;
		while(ptr->next!=NULL && ptr->next->id > id_gs){
			ptr=ptr->next;
		}
		newnode=(nodeGS*)malloc(sizeof(nodeGS));
		newnode->id=id_gs;
		newnode->next=ptr->next;
		ptr->next=newnode;
		return fans;
}
void printGS(nodeGS *fans){

	while(fans!=NULL){
		printf("Id=%d\n",fans->id);
		fans=fans->next;
	}
}
nodeBoth * add_both(nodeBoth *fans,nodeFB *fb_fans, nodeGS *gs_fans){
	nodeBoth *ptr,*newnode;
	
	fans=(nodeBoth *)malloc(sizeof(nodeBoth));
    fans->id=fb_fans->id;
    fans->age=fb_fans->age;
    fb_fans=fb_fans->next;
    fans->next=NULL;
    
    ptr=fans;
    
    int count=0;
    while(gs_fans!=NULL){
        if(count%2==0){
            newnode=(nodeBoth *)malloc(sizeof(nodeBoth));
            newnode->id=gs_fans->id;
            newnode->age=0;
            newnode->next=NULL;
            gs_fans=gs_fans->next;
            ptr->next=newnode;
            ptr=ptr->next;
            
        }
        else{
        	newnode=(nodeBoth *)malloc(sizeof(nodeBoth));
            newnode->id=fb_fans->id;
            newnode->age=fb_fans->age;
            newnode->next=NULL;
            fb_fans=fb_fans->next;
            ptr->next=newnode;
            ptr=ptr->next;
		}
		
		count++;
}
     return fans;
}
void printAll(nodeBoth *fans){
    while(fans!=NULL){
        if(fans->age != 0){
            printf("Id:%d\tAge:%d",fans->id,fans->age);
        }
        else
            printf("Id:%d",fans->id);
            
        fans=fans->next;
        printf("\n");
    }
}




