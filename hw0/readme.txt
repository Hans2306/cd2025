Time complexity O(1) if char already exist

The program uses a linked list to store each character and how many times it appears. 
It also uses an array called charNodes[128] to remember where each character's node is.
When the program sees a character, it first checks the array to see if the character already has a node. 
If it does, the program just increases the count. 
If not, a new node is created for that character, and the address of the node is stored in the array at the character’s position. 
Then, the new node is added to the end of the linked list. 
The array helps the program quickly find out if a node already exists, Time complexity O(1)
making adding or updating characters faster, while the linked list keeps all the characters in order.

該程式使用鏈結串列（Linked List）來存儲每個字元及其出現的次數。
同時，它使用一個名為 charNodes[128] 的陣列來記錄每個字元的節點位置。
當程式讀取一個字元時，會先檢查這個陣列，看該字元是否已經有對應的節點。
如果已經存在，則直接增加計數；
如果不存在，則創建一個新節點，並將其地址存入陣列對應的位置。
接著，這個新節點會被加到鏈結串列的尾端。
這樣，陣列能夠快速找到某個字元是否已經存在，Time complexity O(1)
使新增或更新字元的過程更快，而鏈結串列則保持字元的插入順序。
