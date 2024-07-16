// Bubble Sort
import Dispatch
import Foundation

func bubbleSort(_ array: inout [Int]) {
    let n = array.count
    for i in 0..<n {
        for j in 0..<n-i-1 {
            if array[j] > array[j+1] {
                array.swapAt(j, j+1)
            }
        }
    }
}

// Merge Sort
func mergeSort(_ array: [Int]) -> [Int] {
    guard array.count > 1 else { return array }
    let mid = array.count / 2
    let left = mergeSort(Array(array[..<mid]))
    let right = mergeSort(Array(array[mid...]))
    return merge(left, right)
}

func merge(_ left: [Int], _ right: [Int]) -> [Int] {
    var mergedArray: [Int] = []
    var leftIndex = 0, rightIndex = 0
    while leftIndex < left.count && rightIndex < right.count {
        if left[leftIndex] < right[rightIndex] {
            mergedArray.append(left[leftIndex])
            leftIndex += 1
        } else {
            mergedArray.append(right[rightIndex])
            rightIndex += 1
        }
    }
    mergedArray += left[leftIndex...]
    mergedArray += right[rightIndex...]
    return mergedArray
}

// Quick Sort
func quickSort(_ array: [Int]) -> [Int] {
    guard array.count > 1 else { return array }
    let pivot = array[array.count / 2]
    let less = array.filter { $0 < pivot }
    let equal = array.filter { $0 == pivot }
    let greater = array.filter { $0 > pivot }
    return quickSort(less) + equal + quickSort(greater)
}


// MARK: - Threaded Sorting


// Create a dispatch group
let group = DispatchGroup()

// Create a concurrent queue to synchronize access to the unsorted array
let queue = DispatchQueue(label: "com.example.sorting.queue", attributes: .concurrent)

// Example unsorted array
var unsortedArray = (1...10000).map { _ in Int.random(in: 0...10000) }

// Bubble Sort
group.enter()
DispatchQueue.global().async {
    var bubbleSortArray = [Int]()
    queue.sync { bubbleSortArray = unsortedArray }
    let startTime = Date()
    bubbleSort(&bubbleSortArray)
    let endTime = Date()
    queue.async(flags: .barrier) {
        unsortedArray = bubbleSortArray
        group.leave()
    }
}

// Merge Sort
group.enter()
DispatchQueue.global().async {
    let startTime = Date()
    let sortedArray = mergeSort(unsortedArray)
    let endTime = Date()
    queue.async(flags: .barrier) {
        unsortedArray = sortedArray
        group.leave()
    }
}

// Quick Sort
group.enter()
DispatchQueue.global().async {
    let startTime = Date()
    let sortedArray = quickSort(unsortedArray)
    let endTime = Date()
    queue.async(flags: .barrier) {
        unsortedArray = sortedArray
        group.leave()
    }
}

// Notify when all sorting algorithms have completed
group.notify(queue: .main) {
    print("All sorting algorithms have completed")
}


