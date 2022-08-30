duckdb = require('../../duckdb/tools/nodejs/lib')
nodearrow = require('../')
arrow = require('apache-arrow')

db = new duckdb.Database(":memory:");
db.arrow("SELECT 42 as fortytwo, 'hello' as h", function(err, arrayptr, schemaptr) {
		ipc = nodearrow.arraytoipc(arrayptr, schemaptr)
		reader = arrow.RecordBatchReader.from(ipc);
		batch = reader.readAll()[0];
		console.log(batch.toArray()) // yay
})
