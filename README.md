# CS300 

Data structures course with linked-lists, binary search tree, and Hash tables algorithms. With a minor focus on using pointers, structures, and classes. 


**What was the problem you were solving in the projects for this course?**

-Data structures help organize variables into objects that can then be sorted and searched using different algorithms. Each algorithm has strengths and weaknesses with their time complexity and memory usage. This project explored developing the code for these algorithms and calculating the time complexity in big O notation. 

**How did you approach the problem? Consider why data structures are important to understand.** 

-The scenario for this project was to develop code for a university to take in a course number and course title. The main reason for this is to do a quick search of the database and return a couple of strings of information. The focus was retrieval speed, and this code will likely be on a server, so memory usage has lower priority in this situation. The binary search tree after calculation and testing has an average of 0(log(n)) time complexity. The binary search tree divides the tree in half depending on if the value is greater than or less than the root/ current node. A time complexity of log(n) is the 2nd fastest speed next to constant time. 

**How did you overcome any roadblocks you encountered while going through the activities or project?** 

-The main issue I had was with the parser code given. The .csv file I provided did not have a header and the headerParser function would cause a memory address fault. There was an additional challenge to incorporate prerequisites with the course information and only show courses that are able to apply to base on prerequisites. The parser loads the first line into a header vector, there was a check to make sure every column in the header was filled. Since some courses have prerequisites and others do not, this causes an issue with the code. The row would hold more items or less items than the number of columns in the header. Due to time constraint the additional challenge was dropped, the .csv file had two headers added course number and course title.   

**How has your work on this project expanded your approach to designing software and developing programs?** 

-Understanding how to manipulate a pointer to store information in a structured manner helped me better understand how large information is transfer around.Structures and classes I understood methods, constructors and deconstructors but not the use of them. Understanding the structure creates the objects that are then sorted and inserted into the class. The class handles the objects and a struct creates the objects. A class has private and public members, the private members are dangerous if the user has access to them like pointers. Public methods allow the user to call the internal or private member to manipulate the pointer. 
  
**How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?** 

-Structures and creating objects which hold critical information makes moving information around a lot clearer. The uses of pointers are still confusing but seeing the uses in this code shined some light on their uses. Following OOP software design defiantly clarifies the coding process and helps remove entangled code. I will start implying more OOP design to future code. 
