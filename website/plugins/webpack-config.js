/** @type {import('@docusaurus/types').PluginModule} */
// eslint-disable-next-line no-unused-vars
export default function webpackPlugin(context, options) {
  return {
    name: 'webpack-config-plugin',
    configureWebpack(config) {
      const resolve = config?.resolve ?? {};
      const extensionAlias = resolve?.extensionAlias ?? {};

      return {
        resolve: {
          ...resolve,
          extensionAlias: {
            ...extensionAlias,
            '.js': ['.ts', '.js'],
          },
        },
      };
    },
  };
}
