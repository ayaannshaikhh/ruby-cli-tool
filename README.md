# Ruby CLI Project Manager

A command-line task manager built in Ruby using Thor, SQLite, a custom C extension, and a Rust search module.
This project demonstrates CLI design, database persistence, and cross-language integration between Ruby, C, and Rust.

---

## Features

- Add tasks
- List tasks
- Mark tasks as completed
- Delete tasks
- Search tasks (Rust-powered)
- Persistent storage using SQLite
- Schema initialization from SQL file
- Native C extension for database CRUD operations
- Rust extension for search functionality

---

## Tech Stack

- Ruby
- Thor (CLI framework)
- SQLite
- SQL
- C (Ruby native extension)
- Rust (FFI search module)
- SQLite C API
- rusqlite (Rust SQLite library)
- FFI (Ruby → Rust bridge)

---

## Architecture

This project separates responsibilities across layers:

```
CLI (Thor)
   ↓
TaskManager (Ruby)
   ↓
C extension (CRUD operations)
Rust extension (search functionality)
   ↓
SQLite database
```

---

### Responsibilities

**Ruby**
- CLI commands
- output formatting
- application logic
- schema initialization
- FFI bridge to Rust

**C Extension**
- executes CRUD SQL statements
- interfaces with SQLite via the C API

**Rust Extension**
- performs task search queries
- connects to SQLite using `rusqlite`
- returns formatted results to Ruby

**SQLite**
- persistent storage

---

## Project Structure

```
ruby-cli-tool/
├── bin/
│   └── pm
├── ext/
│   ├── db_ext/
│   │   ├── db_ext.c
│   │   └── extconf.rb
│   └── rust_ext/
│       ├── Cargo.toml
│       └── src/
│           └── lib.rs
├── lib/
│   ├── task_manager.rb
│   └── rust_search.rb
├── db/
│   └── schema.sql
├── Gemfile
└── README.md
```

---

## Installation

Clone the repository:

```
git clone <your-repo-url>
cd ruby-cli-tool
```

Install Ruby dependencies:

```
bundle install
```

Install SQLite (macOS):

```
brew install sqlite
```

Install Rust:

```
curl https://sh.rustup.rs -sSf | sh
```

---

## Build Native Extensions

Build the C extension:

```
cd ext/db_ext
ruby extconf.rb
make
cd ../..
```

Build the Rust extension:

```
cd ext/rust_ext
cargo build --release
cd ../..
```

---

## Setup Database

```
mkdir -p db
touch db/tasks.db
```

---

## Usage

Add a task:

```
bin/pm add "Finish assignment"
```

List tasks:

```
bin/pm list
```

Mark a task as done:

```
bin/pm done 1
```

Delete a task:

```
bin/pm delete 1
```

Search tasks (Rust):

```
bin/pm search "study"
```

---

## Example Session

```
$ bin/pm add "Study Rust"
$ bin/pm add "Study Ruby"
$ bin/pm add "Buy milk"

$ bin/pm search "Stu"
1. [ ] Study Rust
2. [ ] Study Ruby
```

---

## Database Schema

Defined in `db/schema.sql`:

```
CREATE TABLE IF NOT EXISTS tasks(
  id INTEGER PRIMARY KEY,
  title TEXT,
  done INTEGER
);
```

---

## Learning Goals

This project demonstrates:

- Building a CLI tool with Thor
- SQLite database integration
- Writing a Ruby native extension in C
- Integrating Rust with Ruby using FFI
- Using the SQLite C API
- Querying SQLite from Rust using `rusqlite`
- Cross-language software architecture
- Compiling native extensions with `mkmf` and Cargo
- Returning Ruby objects from C code

---

## Future Improvements

- Move remaining database operations into C
- Return structured results from Rust instead of formatted strings
- Prepared statement reuse in C
- Task priorities
- Due dates
- RSpec tests
- Packaging as a Ruby gem
- Colored terminal output
