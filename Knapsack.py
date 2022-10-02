# 0-1 Knapsack problem: DP. Description:

# Given weights and values of n items, put these items in a knapsack of capacity W 
# to get the maximum total value in the knapsack. In other words, given two integer arrays 
# val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items 
# respectively. Also given an integer W which represents knapsack capacity, find out the maximum 
# value subset of val[] such that sum of the weights of this subset is smaller than or equal to W. 
#You cannot break an item, either pick the complete item or don’t pick it (0-1 property).


# W: Max weight
# wt: List of weights
# values: List of values
# n: No. of items
def solveKnapsack(W, wt, values, n):
 
    # Base Case
    if n == 0 or W == 0:
        return 0
 
    if (wt[n-1] > W):
        return solveKnapsack(W, wt, values, n-1)
 
    # return the max of the two possible cases: nth item included or excluded
    else:
        return max(
            values[n-1] + solveKnapsack(
                W-wt[n-1], wt, val, n-1),
            knapSack(W, wt, val, n-1))
 
 

# main driver code
val = [50, 90, 110]
n = len(val)

wt = [10, 20, 30]

W = 50

print knapSack(W, wt, val, n)
 
