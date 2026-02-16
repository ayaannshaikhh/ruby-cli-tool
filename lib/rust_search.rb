require "ffi"

module RustSearch
    extend FFI::Library

    ffi_lib "ext/rust_ext/target/release/librust_ext.dylib"

    attach_function :search_tasks, [:string], :string
end