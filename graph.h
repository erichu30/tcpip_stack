// Forward Declarations
typedef struct node_ node_t;
typedef struct link_ link_t;


// an interface structure which contains name, owning node, and a wire (or link)
typedef struct interface_
{
    char if_name[IF_NAME_SIZE];
    // the pointer to the node it connect to 
    struct node_ *att_node;
    // the pointer to the link of which the interface is a part of
    struct link_ *link;
}interface_t;

struct link_
{
    // each link has two interface to connect two router/end device
    interface_t intf1;
    interface_t intf2;
    unsigned int cost;
}

struct node_
{
    char node_name[NODE_NAME_SIZE];
    // an array to hold the pointers to intrfaces
    // i.e. if this array is empty, it means that there's no interface plugged into the node
    interface_t *intf[MAX_INTF_PER_NODE];
    // a linked list to insert this node to the node graph
    // it is used because we use "glthread" there, and if we use traditional linked list, we don't need this linked list
    glthread_t graph_glue;
}


// a graph structure which is a collection of nodes
typedef struct graph_
{
    /* store the name of topology */
    char toplogy_name[32];
    /* list of nodes */
    // glthread: linked list
    glthread_t node_list;
};
