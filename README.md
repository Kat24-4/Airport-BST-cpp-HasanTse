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

## Credits 
The data used was pulled from OpenFlights.org.
