#include <stdlib.h>
#include <mruby.h>
#include <mruby/string.h>
#include <pthread.h>

static mrb_value
mrb_string_crypt(mrb_state* mrb, mrb_value self) {
  extern char *crypt(const char *, const char *);
  mrb_value str = mrb_nil_value();
  char *res;
  static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

  mrb_get_args(mrb, "S", &str);

  if (pthread_mutex_lock(&m) == 0) {
    mrb_value ret = mrb_nil_value();
    res = crypt(mrb_str_to_cstr(mrb, self), mrb_str_to_cstr(mrb, str));
    if (res) ret = mrb_str_new_cstr(mrb, res);
    pthread_mutex_unlock(&m);
    return ret;
  }
  return mrb_nil_value();
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
