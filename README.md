# EECE 7205 Airport Binary Search Tree - Nashita Hasan, Katherine Tse 
## The Problem 
A travel company needs a fast lookup system that returns information on an airport when given the airport's three-letter IATA code. Additionally, customer agents need to be able to generate alphabetical listings and range queries from the airport data.

## Building and Running the Code 
To build the project run `g++ -std=c++17 -02 src/*.cpp -o airports` in your BASH terminal

To run the project run `./airports` in your BASH terminal and follow the prompts

## Sample Session 

## Task 6: Shape Experiment Table and Explanation
| Build Order | Height | Average Depth | Time for 10,000 Searches | Your Explanation |
| -------- | -------- | -------- |-------- | -------- |
| File order | 177 | 18.3233 | 146 milliseconds | The tree is made by inserting each element one at a time from the top of the file to the bottom of the file. The tree is not guaranteed to be a perfectly balanced binary search tree which can cause additional search time. |
| Sorted Order | 6071  | 3035.5 | 4291 milliseconds | When the tree is inserted in sorted order, it creates a right skewed tree (a single line). This is the worst case scenario for a binary search tree as it acts similarly to a sorted array which heavily increases search times. |
| Balanced | 12  | 10.6532 | 131 milliseconds | When you build a balanced tree, you are guaranteed the most optimal searching strategy because the number of nodes to search is halved with every move. |
| Random | 26 | 13.754 | 154 milliseconds | Similar to the file order run, each element is inserted one at a time from a random order. This would not produce a balanced tree which can add time to searches. |

**Why Random Is Better Than File Order**: The data given is sorted by the ICAO codes. In an ICAO code, the first letter is the region, the second letter is the country, and the last two letters are based on the city name. IATA codes are created by pulling from the city name and if that is not possible, it pulls from the name of the airport. Because of this, IATA codes could still be in a somewhat sorted order just in sections based on geographic location and country. This creates a more skewed tree than a truly random list does.  

## Sample Session Screenshots
### Task 1
<img width="552" height="115" alt="Task1" src="https://github.com/user-attachments/assets/4bfe08ef-2667-49c7-87b8-53fbfa610fce" />

### Task 2
<img width="1622" height="550" alt="Task2" src="https://github.com/user-attachments/assets/ce32d9aa-95fb-426b-9574-bdeb03a12e7b" />

### Task 3
<img width="1598" height="862" alt="Task3" src="https://github.com/user-attachments/assets/310b81da-1e9d-406d-90a4-7ded9919cc57" />

### Task 4
<img width="583" height="310" alt="Task4A" src="https://github.com/user-attachments/assets/3b53f59f-83a1-4256-9705-98d80d6e9f88" />
<img width="1597" height="488" alt="Task4B" src="https://github.com/user-attachments/assets/aedbfcee-72c8-40e0-8298-a9d4d47ece3e" />

### Task 5
<img width="1617" height="197" alt="Task5" src="https://github.com/user-attachments/assets/753d89ae-4276-42bd-90f5-c71526d52a61" />

### Task 6
<img width="566" height="533" alt="Task6" src="https://github.com/user-attachments/assets/f8d84e09-c09b-4e19-bef6-6000b69aae1f" />

## Credits 
The data used was pulled from OpenFlights.org.
