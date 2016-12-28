import rethinkdb as r
r.connect("localhost", 28015).repl()

r.db("food").table("favorites").filter({Person: "Randy"}).run()