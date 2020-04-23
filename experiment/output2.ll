; ModuleID = 'testfile.ll'
source_filename = "testfile.ll"

define i32 @test1(i32 %A) {
  %B = add i32 %A, 0
  ret i32 %B
}

define internal i32 @test(i32 %x) {
  ret i32 %x
}

define i32 @caller() {
  %A = call i32 @test(i32 123)
  ret i32 %A
}
