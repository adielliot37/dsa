# solving knapsack problem using brute force

def knapsack(W, wt, val, n):
    if n == 0 or W == 0: #if the weight and capacity is null
        return 0

    if(wt[n-1] > W): #if weights higher than capacity
        return knapsack(W, wt, val, n-1)

    else:
        return max(val[n-1] + knapsack(W-wt[n-1], wt, val, n-1), knapsack(W, wt, val, n-1))



#testing the function
val = [20, 40, 110]
wt = [10,20,30]
W = 50
n = len(val)
print(knapsack(W, wt, val, n)) 


