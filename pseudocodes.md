## IFT
- The pseudocode is:
```
Function ImageForestingTransform(image, seed):
    Create a distance matrix (dist_matrix) with infinite values, except for the seed pixels
    Create a label matrix (label_matrix) to keep track of the pixel labels
    Initialize an empty priority queue

    For each pixel p in image:
        If p is a seed:
            Add p to priority queue with zero distance
            Set the label of p to the label of the corresponding seed
            Set the distance from p to zero in the distance matrix

    While the priority queue is not empty:
        Remove the current pixel (p_current) from the priority queue
        For each neighbor (n) of p_current:
            Calculate the accumulated distance d from p_current to n
            If the accumulated distance d is less than the current distance n:
                Update the distance from n to d in the distance matrix
                Update label from n to label from p_current in label array
                Add n to the priority queue with distance d

    Return the label array
```