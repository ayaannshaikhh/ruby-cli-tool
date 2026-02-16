# Ruby CLI Project Manager

A command-line task manager built in Ruby using Thor, SQLite, and a custom C extension.
This project demonstrates CLI design, database persistence, and cross-language integration
between Ruby and C using the SQLite C API.

---

## Features

- Add tasks
- List tasks
- Mark tasks as completed
- Delete tasks
- Persistent storage using SQLite
- Automatic database table creation
- Native C extension for database operations

---

## Tech Stack

- Ruby
- Thor (CLI framework)
- SQLite
- C (Ruby native extension)
- SQLite C API

---

## Architecture

This project separates responsibilities across layers:

```
CLI (Thor)
   ↓
TaskManager (Ruby)
   ↓
DBExt (C extension)
   ↓
SQLite C API
   ↓
tasks.db
```

Ruby handles:
- CLI commands
- output formatting
- application logic

C handles:
- executing SQL statements
- interacting with SQLite via the C API

SQLite handles:
- persistent storage

---

## Project Structure

```
ruby-cli-tool/
├── bin/
│   └── pm
├── ext/
│   └── db_ext/
│       ├── db_ext.c
│       └── extconf.rb
├── lib/
│   └── task_manager.rb
├── db/
│   └── tasks.db
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

Install dependencies:

```
bundle install
```

Install SQLite (macOS):

```
brew install sqlite
```

Build the native extension:

```
cd ext/db_ext
ruby extconf.rb
make
cd ../..
```

Ensure the CLI is executable:

```
chmod +x bin/pm
```

Create the database directory if needed:

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

---

## Example Output

```
1. [ ] Finish assignment
2. [x] Study Ruby
```

---

## Database Schema

```
tasks(
  id INTEGER PRIMARY KEY,
  title TEXT,
  done INTEGER
)
```

---

## Learning Goals

This project demonstrates:

- Building a CLI tool with Thor
- SQLite database integration
- Writing a Ruby native extension in C
- Using the SQLite C API
- Cross-language software architecture
- Compiling native extensions with `mkmf`

---

## Future Improvements

- Move remaining database operations into C
- Task priorities
- Due dates
- Search command
- RSpec tests
- Packaging as a Ruby gem
- Colored terminal output
- Connection reuse in the C extension

---