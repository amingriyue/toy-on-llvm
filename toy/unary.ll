Read function definition:
; ModuleID = 'my compiler'
source_filename = "my compiler"

define i32 @"unary!"(i32 %v) {
entry:
%ifcond = icmp ne i32 %v, 0
br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
br label %ifcont

else:                                             ; preds = %entry
br label %ifcont

ifcont:                                           ; preds = %else, %then
%iftmp = phi i32 [ 0, %then ], [ 1, %else ]
ret i32 %iftmp
}

