add_gap_test(test-gap-mlir
    functors.cpp
    views.cpp
)

target_link_libraries(test-gap-mlir
    PRIVATE
        gap-mlir
        MLIRFuncDialect
)