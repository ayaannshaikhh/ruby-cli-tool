use rusqlite::{Connection, Result};
use std::ffi::{CStr, CString};
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn search_tasks(query: *const c_char) -> *mut c_char {
    let c_str = unsafe { CStr::from_ptr(query) };
    let query_str = c_str.to_str().unwrap();

    let result = run_search(query_str).unwrap_or_else(|_| "Search failed".to_string());

    CString::new(result).unwrap().into_raw()
}

fn run_search(query: &str) -> Result<String> {
    let conn = Connection::open("db/tasks.db")?;

    let mut stmt = conn.prepare(
        "SELECT id, title, done FROM tasks WHERE title LIKE ?"
    )?;

    let pattern = format!("%{}%", query);

    let mut rows = stmt.query([pattern])?;

    let mut output = String::new();

    while let Some(row) = rows.next()? {
        let id: i32 = row.get(0)?;
        let title: String = row.get(1)?;
        let done: i32 = row.get(2)?;

        let status = if done == 1 { "[x]" } else { "[ ]" };
        output.push_str(&format!("{}. {} {}\n", id, status, title));
    }

    if output.is_empty() {
        output.push_str("No matches found");
    }

    Ok(output)
}