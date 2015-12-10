#include <errno.h>
#include <string.h>
#include <mruby.h>
#include <mruby/proc.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/variable.h>

static mrb_value
mrb_string_crypt(mrb_state* mrb, mrb_value self) {
  extern char *crypt(const char *, const char *);
  mrb_value str = mrb_nil_value(), ret = mrb_nil_value();
  char *res;

  mrb_get_args(mrb, "S", &str);
  res = crypt(mrb_str_to_cstr(mrb, self), mrb_str_to_cstr(mrb, self));
  if (res) {
    ret = mrb_str_new_cstr(mrb, res);
    free(res);
  }
  return ret;
}

void
mrb_mruby_string_crypt_gem_init(mrb_state* mrb) {
  struct RClass *clazz;

  mrb_define_module_function(mrb, mrb->string_class, "crypt", mrb_string_crypt, MRB_ARGS_REQ(1));
}

void
mrb_mruby_string_crypt_gem_final(mrb_state* mrb) {
  (void)mrb;
}
