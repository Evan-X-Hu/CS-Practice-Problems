double new21Game(int n, int k, int maxPts) {
    
}

// Outline of the algorithm
// Start at 0 points and draw numbers while we have less than k points
// Each draw gains us points in the range [1, maxPts]
// n, k, maxPts is defined by the user on input

// This is probably a math problem because going through all the combinations
// of draws until we are at or above k points would be too much brute force

// We need to find all the outcomes where we are at <=n points
// And we need to find all the outcomes where we are above n points 

// We can see there is a pattern, if we can