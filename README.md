# Placement and Scheduling of Data Intensive Jobs in Edge-Cloud System
## Dhanesh V : 210101117, Ketan Singh : 210101118, Harshit Singh Pakhariya : 210101048

Readme for running the code submitted for CS528 Course Project, Jan-May 2024 Semester.

# Instructions to generate testcase

- To generate test cases,
```
g++ generate_tc.cpp ; a.exe B S K
```
Where
- `B` = Number of chunks that can be hosted in a Cloud Server
- `S` = Number of VMs in a Server
- `K` = Total Number of Jobs

`testcase.txt` will be generated in the same directory.

## TC format
```
B (Number of blocks)
S (Number of VMs in each machine)
K (Total number of jobs)
J1 (Job Id) D1 (Deadline) C1 (Number of Chunks accessed)
C1 Chunk Ids follow
.
.
.
JK DK CK
CK Chunk Ids
```

# Instructions to run the program

## Linear Programming solution
To run the python program for LPP solution using `Gurobipy` library. Note that you might have to install `Gurobi` (academic license version in IITG Intranet), whose instructions can be found at [this link](https://support.gurobi.com/hc/en-us/articles/4534601245713-How-do-I-get-started-with-Gurobi-for-academic-users). Then in terminal,
1. `pip install -r requirements.txt`
2. `python lpp.py <tc file path>`

## Polynomial Main solution
- To run the program for this (in windows):
 ```g++ minimize_nodes.cpp && a.exe <tc file path>```

- If you want to give input in the format mentioned for Test cases through `stdin`,
 ```g++ minimize_nodes.cpp && a.exe```

## First Fit Heuristic solution
- To run the program for this (in windows):
 ```g++ first_fit.cpp && a.exe <tc file path>```
- If you want to give input in the format mentioned for Test cases through `stdin`,
 ```g++ first_fit.cpp && a.exe```

## Best Fit Heuristic solution
- To run the program for this (in windows):
 ```g++ best_fit.cpp && a.exe <tc file path>```
- If you want to give input in the format mentioned for Test cases through `stdin`,
 ```g++ best_fit.cpp && a.exe```

## Trying with only placement constraint
- To run the program for this (in windows):
 ```g++ deadline_oblivious.cpp && a.exe <tc file path>```
- If you want to give input in the format mentioned for Test cases through `stdin`,
 ```g++ deadline_oblivious.cpp && a.exe```