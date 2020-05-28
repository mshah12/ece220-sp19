#include "floorplan.h"

/*This program implements the concept of binary trees and tree travesal to determine then
most efficent floorplan. The is_leaf_node function checks a node in the tree and determines
whether or not it is the leaf node while the is_internal_node function checks a given nodes
and determines if it is an internal node. The is_in_subtree function checks whether a given
node and its children are part of the heirarchy of another person. The rotate function swaps
the width and the height of a given node while the recut function changes the cutline of a
node to its opposite cutline. The swap_module function takes two given nodes and swaps
their module values.The swap_topology function takes two nodes and determines if they are
the left or right child of its parent. It then swaps the parents of the two nodes and changes
the parent's left or right child to the new node. The postfix_traversal takes an expression
array and performs the correct slicing on its modules. The get_total_resource Function
determines all leaf nodes and returns the sum of its values. The init_slicing_tree function
creates a floorplan where all modules are horizontally-aligned and left skewed, meaning they
go form high to low as you move left to right. Overall, this program implements the new ideas
of trees and tree travesal.

partners: ipatel28 */


// Global variables. The global variables will be effectice after the input has been parsed
// by calling the procedure read_module.
int num_modules;                                            // # of input modules.
module_t* modules;                                          // Array for modules.
int sum = 0;                                                // intializes global sum for get_total_resource function

// Procedure: floorplan
// The major procedure of the floorplan. The procedure concists of the following major steps:
// - initialize the slicing tree.
// - print the information of the slicing tree.
// - perform the optimization process.
void floorplan(const char file[]) {

  /*printf("\n********************************** MP11 **********************************\n");

  // Read the modules from the given input file.
  read_modules(file);

  // Initialize the slicing tree. You can replace the function init_slicing_tree with the function
  // challenge_init_slicing_tree if you accomplish the challenge implementation.
  node_t* root = init_slicing_tree(NULL, 0);
  int num_nodes = (num_modules << 1) - 1;
  printf("Initial slicing tree: Root=%p, num_nodes=%d, num_modules=%d\n", root, num_nodes, num_modules);

  // Obtain the expression of the initial slicing tree.
  expression_unit_t* expression = (expression_unit_t*)calloc(num_nodes, sizeof(expression_unit_t));
  get_expression(root, num_nodes, expression);
  printf("Initial expression: ");
  pnt_expression(expression, num_nodes);
  double area = packing(expression, num_nodes);
  printf("Initial area: %.5e\n", area);
  draw_modules("init.png");
  free(expression);

  // Perform the optimization process.
  printf("Perform optimization...\n");
  area = optimize(root, num_nodes);
  pnt_modules();
  printf("Packing area = %.5e (has overlapped? %d (1:yes, 0:no))\n", area, is_overlapped());

  // Output your floorplan.
  printf("Draw floorplan to %s\n", outfile);
  draw_modules(outfile);

  printf("********************************** END ***********************************\n");*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS/PROCEDURES YOU HAVE TO FINISH.                                                      //
///////////////////////////////////////////////////////////////////////////////////////////////////



// Function: is_leaf_node
// Return 1 if the given slicing tree node is a leave node, and 0 otherwise.
int is_leaf_node(node_t* ptr) {
  // TODO: (remember to modify the return value appropriately)

  // checks if the node has any children
  if(ptr->left == NULL && ptr->right == NULL)
  {
    return 1;
  }

  // returns 0 if the node has children
  return 0;
}

// Function: is_internal_node
// Return 1 if the given slicing tree node is an internal node, and 0 otherwise.
int is_internal_node(node_t* ptr) {
  // TODO: (remember to modify the return value appropriately)

  // checks if the node has at least one child
  if(ptr->left != NULL || ptr->right != NULL)
  {
    return 1;
  }

  // returns 0 if the node has children
  return 0;
}

// Function: is_in_subtree
// Return 1 if the given subtree rooted at node 'b' resides in the subtree rooted at node 'a'.
int is_in_subtree(node_t* a, node_t* b) {
  // TODO: (remember to modify the return value appropriately)

  // creates a temporary node that equals node b
  node_t *bparent = b;

  // checks if any of the node b's parents are childrens of node a
  // returns 1 if they b is in the subtree of a
  while(bparent != NULL)
  {
    if(bparent == a)
    {
      return 1;
    }
    else
    {
      bparent = bparent->parent;
    }
  }

  // returns 0 if the node is not in the subtree of the other node
  return 0;
}

// Procedure: rotate
// Rotate a module from a given leave node of the slicing tree by 90 degree. That is, the height
// and the width of the modules are swapped.
void rotate(node_t* ptr) {
  // TODO:

  // declares a temporary variable to hold the value of the width
  int temp;
  temp = ptr->module->w;

  // changes height to width and width to height
  ptr->module->w = ptr->module->h;
  ptr->module->h = temp;
  return;
}

// Procedure: recut
// Change the cutline of a module in a given internal node of the slicing tree.
// If the original cutline is a vertical cutline, the resulting cutline should be changed to
// horizontal and vice versa.
void recut(node_t* ptr) {
  if(!is_internal_node(ptr)) return;
  assert(ptr->module == NULL && ptr->cutline != UNDEFINED_CUTLINE);

  // TODO:

  // checks if the cutline is vertical
  if(ptr->cutline == V)
  {
    // changes cutline to horizontal if it is previously vertical
    ptr->cutline = H;
  }
  else
  {
    // changes cutline to vertical if it is perviously horizontal
    ptr->cutline = V;
  }
  return;
}

// Procedure: swap_module
// Swap the two modules between two given leave nodes in the slicing tree.
void swap_module(node_t* a, node_t* b) {
  if(!is_leaf_node(a) || !is_leaf_node(b)) return;
  assert(a->module != NULL && a->cutline == UNDEFINED_CUTLINE);
  assert(b->module != NULL && b->cutline == UNDEFINED_CUTLINE);

  // creates a temporary module to hold to value of one node's module
  module_t *temp;
  temp = a->module;

  // changes the module of a to the module of b and vice versa
  a->module = b->module;
  b->module = temp;
  return;
  // TODO:
}

// Procedure: swap_topology
// Swap the topology of two subtrees rooted at two given nodes of the slicing tree.
// The procedure applies "is_in_subtree" first to tell if any of the subtree belongs
// to a part of the other.make
void swap_topology(node_t* a, node_t* b) {
  if(a == NULL || b == NULL) return;
  if(a->parent == NULL || b->parent == NULL) return;
  if(is_in_subtree(a, b) || is_in_subtree(b, a)) return;
  assert(a->parent != NULL && b->parent != NULL);
  // TODO:

  // declares a temporary node to hold the value of a node
  node_t *tempParent;

  // checks if a is the left or right child
  if(a->parent->left == a)
  {
    // sets b to be the left child of a's parent
    a->parent->left = b;
  }
  else
  {
    // sets b to be the right child of a's parent
    a->parent->right = b;
  }

  // checks if b is the left or right child
  if(b->parent->left == b)
  {
    // sets a to be the left child
    b->parent->left = a;
  }
  else
  {
    // sets a to be the right child
    b->parent->right = a;
  }

  // switches the parent values of both a and b
  tempParent = a->parent;
  a->parent = b->parent;
  b->parent = tempParent;

  return;

}

// Procedure: get_expression
// Perform the post-order traversal on the given slicing tree and stores the polish expression
// into the given expression array. You should assume the expression array is pre-allocated with
// size N. In other words, you don't have to perform dynamic memory allocation. In fact, there
// is no need for you to add any code here, but it would be better if you can understand the
// details of this procedure especially the last two lines where the procedure postfix_traversal
// is called internally to obtain the expression.
void get_expression(node_t* root, int N, expression_unit_t* expression) {
  int i;
  // Clear the expression.
  for(i=0; i<N; ++i) {
    expression[i].module = NULL;
    expression[i].cutline = UNDEFINED_CUTLINE;
  }

  // Obtain the expression using the postfix traversal.
  int nth = 0;
  postfix_traversal(root, &nth, expression);
}

// Procedure: postfix_traversal
// Perform the postfix traversal on the slicing tree and store the corresponding polish expression
// to the given expression array. You should use the pointer "nth" to find out the index of the
// expression array and write the data accordingly. Notice that the expression array is a sequence
// of expression units which could be either a module pointer or the cutline type. If the module
// pointer exists in the expression unit, you should set the corresponding cutline type to
// "UNDEFINED_CUTLINE". On the other hand, if the expression unit is a cutline type, you should
// assign NULL to the corresponding module pointer.
void postfix_traversal(node_t* ptr, int* nth, expression_unit_t* expression) {

  // checks the base case which is checking if the node is NULL
  if(ptr == NULL)
  {
    return;
  }

  // performs recursion on the left and ride branches of the node
  postfix_traversal(ptr->left, nth, expression);
  postfix_traversal(ptr->right, nth, expression);

  // if the module of the node does not exist, set its cutline to UNDEFINED
  if(ptr->module != NULL)
  {
    expression[*nth].module = ptr->module;
    expression[*nth].cutline = UNDEFINED_CUTLINE;
  }

  // change node's module to a value of 0 and change its cutline
  else
  {
    expression[*nth].module = NULL;
    expression[*nth].cutline = ptr->cutline;
  }

  // increment the index in the expression array
  (*nth) += 1;
  return;

  // TODO:
}

// get_total_resource
// traverse through the tree and return the sum of all resource for each module
int get_total_resource(node_t* ptr)
{
  // TODO:

  // if node does not exist, return sum of 0
  if(ptr == NULL)
  {
    return sum;
  }

  // checks if node is a leaf node. Adds its resource value to sum if it is
  if(ptr->left == NULL && ptr->right == NULL)
  {
    sum += ptr->module->resource;
    return sum;
  }

  // recursivly traverses through the tree checking every node and returning its sum
  get_total_resource(ptr->left);
  get_total_resource(ptr->right);
  return sum;
}

// Procedure: init_slicing_tree
// Initialize the slicing tree by aligning modules along the horizontal line. In this procedure
// you should produce a left-skewed tree. The right child of any internal node should be a leave
// node and the subtree is recursively expanded down to the left. Take 5 modules for an example.
// The resulting tree should look like:
/*
                      root
                      /  \
                     i1  m0
                    /  \
                   i2  m1
                  /  \
                 i3  m2
                /  \
               m4  m3
*/
// where the prefix i denotes an internal node (including root), and the prefix m denotes a leave
// node. Notice that each node is either an internal in which the cutline type is specified or
// a leave in which the module pointer is assigned. For an internal node, the value of its module
// pointer should be assigned by NULL. For a leave node, the value of its cutline type should be
// specified as "UNDEFINED_CUTLINE".
//
// In each recursive step of this function, you are passed by a parent pointer pointing to the
// parent node of which node you will generate at this step, as well as an integer index n
// indicating the depth of the current recursion and the index of the module array to which the
// module pointer of the leave node should point to.
//
node_t* init_slicing_tree(node_t* par, int n) {

  assert(n >= 0 && n < num_modules);

  // TODO:

  // checks if the index of the array is within bounds
  if(n == num_modules - 1)
  {
    // dynamically allocates memory for a new node for the left side
    node_t * leftChild = (node_t *) malloc(sizeof(node_t));

    // intializes the values for the left node and sets values
    leftChild->module = &(modules[n]);
    leftChild->cutline = UNDEFINED_CUTLINE;
    leftChild->left = NULL;
    leftChild->right = NULL;
    leftChild->parent = par;
    par->left = leftChild;

    // dyamically allocates memory for a new node for the right side
    node_t* rightChild = (node_t *) malloc(sizeof(node_t));

    // intializes the values for the right node and sets values
    rightChild->module = &(modules[n-1]);
    rightChild->cutline = UNDEFINED_CUTLINE;
    rightChild->left = NULL;
    rightChild->right = NULL;
    rightChild->parent = par;
    par->right = rightChild;

    return leftChild;
  }

  // create another left node
  node_t * leftChild2 = (node_t *) malloc(sizeof(node_t));

  // declares and intializes the values of the node
  leftChild2->module = NULL;
  leftChild2->cutline = V;
  leftChild2->parent = par;

  // checks if the parent node is the top node
  if(par != NULL)
  {

    // dynamically allocate memory for a new right node
    node_t * rightChild2 = (node_t *) malloc(sizeof(node_t));

    // declare and intialize the values of the right node
    rightChild2->module  = &(modules[n-1]);
    rightChild2->cutline = UNDEFINED_CUTLINE;
    rightChild2->left = NULL;
    rightChild2->right = NULL;
    rightChild2->parent = par;
    par->right = rightChild2;

    // sets parent's left child to leftChild2 if it is not the parent node
    par->left = leftChild2;
  }

  // traverses through the tree recursively
  init_slicing_tree(leftChild2, n+1);

  return leftChild2;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// PREDEFINED FUNCTIONS AND PROCEDURES.                                                          //
// PLEASE DO NOT MODIFY ANY FIELD STARTING HERE.                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////

// Function: is_overlapped
// Return 1 if any overlaps among modules, and 0 otherwise.
int is_overlapped() {
  int i, j;
  int llxi, llyi, urxi, uryi;
  int llxj, llyj, urxj, uryj;
  int flag = 0;
  for(i=0; i<num_modules; ++i) {
    llxi = modules[i].llx;
    llyi = modules[i].lly;
    urxi = llxi + modules[i].w;
    uryi = llyi + modules[i].h;
    for(j=i+1; j<num_modules; ++j) {
     llxj = modules[j].llx;
     llyj = modules[j].lly;
     urxj = llxj + modules[j].w;
     uryj = llyj + modules[j].h;

     int rxu = MIN(urxi, urxj);
     int ryu = MIN(uryi, uryj);
     int rxl = MAX(llxi, llxj);
     int ryl = MAX(llyi, llyj);

     if(rxu>rxl && ryu>ryl) {
       flag = 1;
       printf("module %d and %d overlaps.\n", modules[i].idx, modules[j].idx);
     }
    }
  }
  return flag;
}

// Procedure: pnt_expression
// Print the expression to the display.
void pnt_expression(expression_unit_t *expression, int N) {

  if(!is_valid_expression(expression, N)) {
    printf("Invalid expression. Can't print. Please check your get_expression procedure.\n");
    return;
  }

  int i;
  for(i=0; i<N; ++i) {
    if(expression[i].cutline == UNDEFINED_CUTLINE) {
      assert(expression[i].module != NULL);
      printf("%d", expression[i].module->idx);
    }
    else {
      assert(expression[i].module == NULL);
      printf("%c", expression[i].cutline == V ? 'V' : 'H');
    }
  }
  putchar('\n');
}

// Procedure: pnt_modules
// Print the coordinates of each module.
void pnt_modules() {
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("Module %d is placed at (%d, %d) with height=%d and width=%d\n",
            modules[i].idx,
            modules[i].llx,
            modules[i].lly,
            modules[i].h,
            modules[i].w);
  }
}

// Procedure: write_modules
// Write the coordinates of each module into a file.
void write_modules(const char file[]) {
  FILE *ofp = fopen(file, "w");
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("%d %d %d %d %d\n",
            modules[i].idx,
            modules[i].llx,
            modules[i].lly,
            modules[i].h,
            modules[i].w);
  }
  fclose(ofp);
}

// Function: get_module
// Return the module pointer to the module with the given idx.
module_t* get_module(int idx) {
  int i;
  for(i=0; i<num_modules; ++i) {
    if(idx == modules[i].idx) return &modules[i];
  }
  return NULL;
}

// Function: packing
// The main procedure of packing modules. The procedure takes the expression from the
// current slicing tree and then compute the coordinate of each module.
double packing(expression_unit_t* expression, int N) {

  if(!is_valid_expression(expression, N)) {
    return FLT_MAX;
  }

  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));

  // Iterates through the expression
  int i, j;
  cluster_t cluster, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      assert(expression[i].cutline == UNDEFINED_CUTLINE);

      // Adjust the coordinate of the module.
      expression[i].module->llx = 0;
      expression[i].module->lly = 0;

      // Create a cluster.
      cluster.beg = i;
      cluster.end = i;
      cluster.w = expression[i].module->w;
      cluster.h = expression[i].module->h;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      assert(expression[i].cutline != UNDEFINED_CUTLINE);
      assert(stack_top >= 2);

      // Extract the top two clusters.
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];

      // Create a new cluster.
      cluster.beg = cluster_l.beg;
      cluster.end = cluster_r.end;

      // Horizontal cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster.
      // - x coordinate doesn't change.
      if(expression[i].cutline == H) {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->lly += cluster_l.h;
        }
        cluster.w = cluster_l.w > cluster_r.w ? cluster_l.w : cluster_r.w;
        cluster.h = cluster_l.h + cluster_r.h;
      }
      // Vertical cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster.
      // - y coordinate doesn't change.
      else {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->llx += cluster_l.w;
        }
        cluster.w = cluster_l.w + cluster_r.w;
        cluster.h = cluster_l.h > cluster_r.h ? cluster_l.h : cluster_r.h;
      }

      // Insert the cluster into the stack.
      stack[stack_top++] = cluster;
    }
  }

  assert(stack_top == 1);

  double area = (double)stack[stack_top - 1].w * (double)stack[stack_top - 1].h;

  free(stack);

  return area;
}

// Function: is_valid_expression
int is_valid_expression(expression_unit_t* expression, int N) {

  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));

  // Iterates through the expression
  int i;
  cluster_t cluster = {0, 0, 0, 0}, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      if(expression[i].cutline != UNDEFINED_CUTLINE) return 0;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      if(expression[i].cutline == UNDEFINED_CUTLINE) return 0;
      if(stack_top < 2) return 0;
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];
      stack[stack_top++] = cluster;
    }
  }
  free(stack);
  return stack_top == 1;
}

// Procedure: read_modules
// Read the modules from a given input file and initialize all required data structure.
void read_modules(const char file[]) {

  int i;
  FILE* ifp = fopen(file, "r");

  assert(ifp != NULL);

  // Read the number of modules.
  assert(fscanf(ifp, "%d", &num_modules) == 1);
  assert(num_modules >= 2);

  // Allocate the memory.
  modules = (module_t*)malloc(num_modules*sizeof(module_t));

  // Read the modules one by one.
  for(i=0; i<num_modules; ++i) {
    assert(fscanf(ifp, "%d %d %d %d", &modules[i].idx, &modules[i].w, &modules[i].h, &modules[i].resource) == 4);
    modules[i].llx = 0;
    modules[i].lly = 0;
  }

  fclose(ifp);
}

// Procedure: copy_expression
void copy_expression(expression_unit_t* lhs, expression_unit_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(expression_unit_t));
}

// Procedure: copy_modules
void copy_modules(module_t* lhs, module_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(module_t));
}

// Function: accept_proposal
// Accept the proposed solution.
int accept_proposal(double current, double proposal, double temperature) {
  if(proposal < current) return 1;
  if(temperature <= FROZEN) return 0;
  double prob = exp(-(double)(proposal - current) / temperature);
  return rand()/(double)RAND_MAX < prob;
}

// Function: get_rand_internal
node_t* get_rand_internal(node_t** internals, int num_internals) {
  return internals[rand()%num_internals];
}

// Function: get_rand_leave
node_t* get_rand_leave(node_t** leaves, int num_leaves) {
  return leaves[rand()%num_leaves];
}

// Function: get_random_node
node_t* get_rand_node(node_t** internals, int num_internals, node_t** leaves, int num_leaves) {
  if(rand()%2) {
    return get_rand_leave(leaves, num_leaves);
  }
  return get_rand_internal(internals, num_internals);
}

// Function: optimize
// Optimize the area of the floorplanner.
double optimize(node_t *root, int num_nodes) {

  // Storage for leave and internal nodes.
  int head = 0;
  int tail = 0;
  int num_leaves = 0;
  int num_internals = 0;
  node_t** queue = (node_t**)malloc(num_nodes*sizeof(node_t*));
  node_t** leaves = (node_t**)malloc(num_modules*sizeof(node_t*));
  node_t** internals = (node_t**)malloc((num_modules-1)*sizeof(node_t*));
  node_t* u;
  queue[tail++] = root;

  while(tail - head) {
    u = queue[head++];

    if(u->module) {
      assert(u->cutline == UNDEFINED_CUTLINE);
      leaves[num_leaves++] = u;
    }
    else {
      assert(u->cutline != UNDEFINED_CUTLINE);
      internals[num_internals++] = u;
    }

    if(u->left) queue[tail++] = u->left;
    if(u->right) queue[tail++] = u->right;
  }

  assert(num_leaves == num_modules);
  assert(num_internals == num_modules - 1);

  // Simulated annealing.
  srand(time(0));
  expression_unit_t* best_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  expression_unit_t* curr_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  module_t* best_modules = (module_t*)malloc(num_modules*sizeof(module_t));

  int i, key;
  double best_area, curr_area;
  double temperature = 100.0;
  node_t* a;
  node_t* b;

  // Initialization.
  get_expression(root, num_nodes, best_expression);
  best_area = packing(best_expression, num_nodes);
  memcpy(best_modules, modules, num_modules*sizeof(module_t));

  while(temperature > FROZEN) {

    // Generate the neighboring solution.
    for(i=0; i<MAX_NUM_RAND_STEPS; ++i) {

      key = rand()%4;

      switch(key) {

        // Perform recut.
        case 0:
          recut(get_rand_internal(internals, num_internals));
        break;

        // Perform rotate.
        case 1:
          rotate(get_rand_leave(leaves, num_leaves));
        break;

        // Perform swap_module.
        case 2:
          do {
            a = get_rand_leave(leaves, num_leaves);
            b = get_rand_leave(leaves, num_leaves);
          } while(a == b);
          swap_module(a, b);
        break;

        // Perform swap_topology.
        default:
          do {
            a = get_rand_node(internals, num_internals, leaves, num_leaves);
            b = get_rand_node(internals, num_internals, leaves, num_leaves);
          } while(is_in_subtree(a, b) || is_in_subtree(b, a));
          swap_topology(a, b);
        break;
      }

      // Evaluate the area.
      get_expression(root, num_nodes, curr_expression);
      curr_area = packing(curr_expression, num_nodes);
      if(curr_area < best_area) {
        best_area = curr_area;
        copy_expression(best_expression, curr_expression, num_nodes);
        memcpy(best_modules, modules, num_modules*sizeof(module_t));
        //copy_modules(best_modules, modules, num_modules);
      }
    }
    temperature *= TEMPERATURE_DECREASING_RATE;
  }

  memcpy(modules, best_modules, num_modules*sizeof(module_t));
  best_area = packing(best_expression, num_nodes);

  /*// Secondary optimization.
  temperature = 100.0;
  while(temperature > FROZEN) {

    // Start at a step.
    copy_expression(curr_expression, best_expression, num_nodes);
    copy_modules(modules, best_modules, num_modules);

    // Generate the neighboring solution.
    for(i=0; i<MAX_NUM_RAND_STEPS; ++i) {

      copy_expression(next_expression, curr_expression, num_nodes);

      key = rand()%4;

      switch(key) {

        // Perform recut.
        case 0:
          do{
            j = rand() % num_nodes;
          } while(next_expression[j].cutline == UNDEFINED_CUTLINE);
          next_expression[j].cutline = next_expression[j].cutline == V ? H : V;
        break;

        // Perform rotate.
        case 1:
          do{
            j = rand() % num_nodes;
          } while(next_expression[j].module == NULL);
          next_expression[j].module->w = next_expression[j].module->w ^ next_expression[j].module->h;
          next_expression[j].module->h = next_expression[j].module->w ^ next_expression[j].module->h;
          next_expression[j].module->w = next_expression[j].module->w ^ next_expression[j].module->h;

        break;

        // Perform swap_module.
        case 2:
          do {
            j = rand() % num_nodes;
            k = rand() % num_nodes;
          } while(j == k || next_expression[j].module == NULL || next_expression[k].module == NULL);
          tmp = next_expression[k].module;
          next_expression[k].module = next_expression[j].module;
          next_expression[j].module = tmp;
        break;

        // Perform swap_topology.
        default:
          do {
            do{
              j = rand() % num_nodes;
              k = rand() % num_nodes;
            } while(j == k);
            e = next_expression[k];
            next_expression[k] = next_expression[j];
            next_expression[j] = e;
          } while (!is_valid_expression(next_expression, num_nodes));
        break;
      }

      // Evaluate the area.
      curr_area = packing(curr_expression, num_nodes);
      next_area = packing(next_expression, num_nodes);
      if(accept_proposal(curr_area, next_area, temperature)){
        if(next_area < best_area) {
          best_area = next_area;
          copy_expression(best_expression, next_expression, num_nodes);
        }
        copy_expression(curr_expression, next_expression, num_nodes);
        curr_area = next_area;
      }
    }
    temperature *= TEMPERATURE_DECREASING_RATE;
  }

  best_area = packing(best_expression, num_nodes);*/


  free(queue);
  free(leaves);
  free(internals);
  free(best_expression);
  free(curr_expression);
  free(best_modules);

  return best_area;
}
