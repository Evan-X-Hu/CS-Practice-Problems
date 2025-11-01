from typing import List
class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        colLen = len(matrix)
        rowLen = len(matrix[0])
        loopNum = 0
        a = 0
        b = colLen - 1

        # loop bounds
        start = 0
        end = 0

        result = []

        while(True):
            # --> movement
            start = a
            end = rowLen - (loopNum + 1)
            if(start > end): 
                break
            for x in range(start, end):
                result.append(matrix[a][x])

            # v   movement
            start = a + 1
            end = b
            if(start > end): 
                break
            for x in range(start, end):
                result.append(matrix[x][rowLen - (loopNum)])
            
            # <-- movement
            start = rowLen - (loopNum + 2)
            end = loopNum
            if(start < end):
                break
            for x in range(start, end, -1):
                result.append(matrix[b][x])

            # ^  movement
            start = b - 1
            end = a + 1
            if(start < end):
                break
            for x in range(start, end, -1):
                result.append(matrix[x][loopNum])

