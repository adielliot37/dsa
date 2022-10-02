function approachingFibonacci(arr) {
  let num1 = 0;
  let num2 = 1;
  let num3 = 1;
  let result = 0;
  let sum = 0;

  for (let i = 0; i < arr.length; i++) {
    sum += arr[i]
  }

  for (let i = 0; i <= sum; i++) {
    if (num1 == sum) {
      return result;
    }

    if (num1 <= sum) {
      result = num2 - sum;
    }

    num1 = num2;
    num2 = num3;
    num3 = num1 + num2;
  }

  return result;
}

// Input: [5, 2, 1]
// Output: 0

// Input: [1, 20, 2, 5]
// Output: 6

console.log(approachingFibonacci([5, 2, 1]))
console.log(approachingFibonacci([1, 20, 2, 5]))
