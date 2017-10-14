import Foundation

var d = [String: Int]()
let n = Int(readLine()!)!


for i in 0..<n {
    let s = readLine()!
    if d[s] == nil {
        d[s] = 1
    }
    else {
        d[s]! += 1
    }
}

let Qn = Int(readLine()!)!

var q = [String]()

for i in 0..<Qn {
    print(d[readLine()!] ?? 0)
}
