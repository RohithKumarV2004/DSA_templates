class NumArray {
    int n;
    vector<int> tree;
    void buildTree(vector<int> &nums){
        //filling all the leaf nodes with the values
        for(int i=n, j=0; i<2*n, j<n; i++, j++){
            tree[i]=nums[j];
        }
        //fill all the parent nodes in reverse order (bottom-up)
        for(int i=n-1; i>=0; i--){
            tree[i]=tree[2*i]+tree[2*i+1]; //max,min
        }
    }
public:
    NumArray(vector<int>& nums) {
        n=nums.size();
        tree.resize(2*n);
        buildTree(nums);
    }
    
    void update(int pos, int val) {
        pos+=n;
        tree[pos]=val;
        //update all the parent values until root
        while(pos>0){
            //first assign left and right sibling to be pos
            int l=pos;
            int r=pos;
            //if pos is even, then it is a left child, so it's right sibling is pos+1
            if(pos%2==0){
                r=pos+1;
            }
            //if pos is odd, then it's a right child, then left sibling is pos-1
            else{
                l=pos-1;
            }
            //update it's parent value
            tree[pos/2]=tree[l]+tree[r]; //max,min
            //go to it's parent
            pos=pos/2;
        }
    }
    
    int sumRange(int left, int right) {
        //get to the respective leaf nodes
        left+=n;
        right+=n;
        int sum=0;
        //do this until they don't cross each other
        while(left<=right){
            //if left is a right child, then add the value and increment left
            if(left%2==1){
                sum+=tree[left]; //max, min
                left++;
            }
            //if right is a left child, then add the value and decrement right
            if(right%2==0){
                sum+=tree[right]; //max, min
                right--;
            }
            //go to the previous level
            left/=2;
            right/=2;
        }
        return sum;
    }
};
