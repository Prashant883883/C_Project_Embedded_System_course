const express = require("express");
const sqlite3 = require("sqlite3").verbose();
const app = express();

app.use(express.json());

// ------------------------------
// Connect to SQLite Database
// ------------------------------
const db = new sqlite3.Database("./users.db", (err) => {
    if (err) {
        console.error("Database error:", err.message);
    } else {
        console.log("Connected to SQLite database.");
    }
});

// ------------------------------
// Create users table (if missing)
// ------------------------------
db.run(`
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT,
        email TEXT
    )
`);

// ------------------------------
// POST /users  → Add a user
// ------------------------------
app.post("/users", (req, res) => {
    const { name, email } = req.body;

    db.run(
        "INSERT INTO users (name, email) VALUES (?, ?)",
        [name, email],
        function (err) {
            if (err) {
                return res.status(500).json({ error: err.message });
            }
            res.json({ message: "User added", id: this.lastID });
        }
    );
});

// ------------------------------
// GET /users  → Get all users
// ------------------------------
app.get("/users", (req, res) => {
    db.all("SELECT * FROM users", [], (err, rows) => {
        if (err) {
            return res.status(500).json({ error: err.message });
        }
        res.json(rows);
    });
});

// ------------------------------
// Start the server
// ------------------------------
app.listen(3000, () => {
    console.log("🔥 Server running on http://localhost:3000");
});
