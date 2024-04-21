# Test Case Readme

To generate test cases,
```
g++ generate_tc.cpp ; a.exe B S K
```
Where
- `B` = Number of chunks that can be hosted in a Cloud Server
- `S` = Number of VMs in a Server
- `K` = Total Number of Jobs

`RP_testcase.txt` is the testcase in example figure of research paper.

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

