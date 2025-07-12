fn main() {
    let boom: *const i32 = std::ptr::null();

    unsafe {
        println!("Valor do ponteiro nulo: {}", *boom);
    }
}
