def heapsortMax(arr):
	buildMaxHeap(arr)
	i = len(arr)
	while i != 1:
		arr[1], arr[i] = arr[i], arr[1]
		heapifyMax(arr, i)
		i = i - 1
			
def buildMaxHeap(arr):
	i = len(arr) / 2
	while i != 0:
		heapifyMax(arr, i)
		i = i - 1
	
def heapifyMax(arr, i):
	largest = i
	l = 2 * i
	r = 2 * i + 1
	
	if(l <= len(arr) and arr[l] > arr[i]):
		largest = l
	else:
		largest = i
	if(r <= len(arr) and arr[r] > arr[i]):
		largest = r
		
	if(largest != i):
		arr[i], arr[largest] = arr[largest], arr[i]
		heapMax(arr, largest)
		
def heapMax(arr):
	return arr[1]
