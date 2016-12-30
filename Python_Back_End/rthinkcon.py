import rethinkdb as r
r.connect("localhost", 28015).repl()

a = r.db("geothermal").table("log_mustikajaya").run()
for b in a:
    print (b)
