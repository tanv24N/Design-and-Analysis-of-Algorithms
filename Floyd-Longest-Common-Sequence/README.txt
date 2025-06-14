This project implements two classic dynamic programming algorithms:

1. **Longest Common Subsequence (LCS)**  
   - Input: Two alphabetic strings (≤100 characters)  
   - Output: Length and content of their LCS  
   - Example:  
     ```
     ./lcs ABCDEfghi AcbDedghaq
     Output:
     Length of LCS: 4
     LCS: ADgh
     ```

2. **Floyd's All-Pairs Shortest Paths**  
   - Input: One or more complete undirected graphs (from a file)  
   - Output:  
     - Number of vertices  
     - Pointer matrix (P)  
     - Shortest paths between all vertex pairs with distances  
   - Example:  
     ```
     ./floyd graph.txt
     Output:
     Problem 1: n = 6
     Pointer matrix P[6][6]:
     ...
     V1–V5: 1 4 5 (Distance: 9)
     ```

## Compilation
Use the provided Makefile:
```bash
make