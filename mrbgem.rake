MRuby::Gem::Specification.new('mruby-string-crypt') do |spec|
  spec.license = 'MIT'
  spec.authors = 'mattn'
  spec.version = '0.0.1'

  if build.toolchains.include?("androideabi")
    spec.cc.flags << '-DHAVE_PTHREADS'
  else
    spec.linker.libraries << ['pthread']
  end
end
