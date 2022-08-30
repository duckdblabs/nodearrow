#define NODE_ADDON_API_DISABLE_DEPRECATED

#include <napi.h>
#include <arrow/c/abi.h>
#include <arrow/c/bridge.h>
#include <arrow/io/api.h>
#include <arrow/buffer.h>
#include <arrow/ipc/writer.h>

namespace nodearrow {
    // TODO we should probably have a separate step that creates this writer
    static Napi::Value ArrayToIpc(const Napi::CallbackInfo &info) {

        auto env = info.Env();

        if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
            Napi::TypeError::New(env, "Need carray and schema pointers").ThrowAsJavaScriptException();
            return env.Null();
        }

        auto carray = (ArrowArray *) (ptrdiff_t) info[0].As<Napi::Number>().Int64Value();
        auto cschema = (ArrowSchema *) (ptrdiff_t) info[1].As<Napi::Number>().Int64Value();
        auto schema = arrow::ImportSchema(cschema);
        if (!schema.ok()) {
            // TODO complain
        }
        auto batch = arrow::ImportRecordBatch(carray, *schema);

        if (!batch.ok()) {
            // TODO complain
        }

        auto output_stream = arrow::io::BufferOutputStream::Create();
        if (!output_stream.ok()) {
            // TODO complain
        }
        auto batch_writer = arrow::ipc::MakeStreamWriter(*output_stream, *schema);

        if (!batch_writer.ok()) {
            // TODO complain
        }

        auto status = (*batch_writer)->WriteRecordBatch(**batch);

        if (!status.ok()) {
            // TODO complain
        }

        auto buffer = (*output_stream)->Finish();

        if (!buffer.ok()) {
            // TODO complain
        }

        // TODO take over buffer ownership and dont copy
        auto buf = Napi::ArrayBuffer::New(env, (*buffer)->size());
        memcpy(buf.Data(), (const void *) (*buffer)->address(), (*buffer)->size());
        return buf;
    }
}

namespace {

    Napi::Object RegisterModule(Napi::Env env, Napi::Object exports) {
        Napi::HandleScope scope(env);
        exports.Set("arraytoipc", Napi::Function::New(env, nodearrow::ArrayToIpc));
        return exports;
    }

} // namespace

NODE_API_MODULE(nodearrow, RegisterModule);
