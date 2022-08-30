duckdb = require('../../duckdb/tools/nodejs/lib')
nodearrow = require('../lib')

db = new duckdb.Database(":memory:");
db.arrow("SELECT 42", function(err, arrayptr, schemaptr) {

	console.log(arrayptr);
		console.log(schemaptr);
		console.log(nodearrow.arraytoipc(arrayptr, schemaptr))

})
