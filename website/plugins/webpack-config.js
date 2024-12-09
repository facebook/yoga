/** @type {import('@docusaurus/types').PluginModule} */
// eslint-disable-next-line no-unused-vars
export default function webpackPlugin(context, options) {
  return {
    name: 'webpack-config-plugin',
    // eslint-disable-next-line no-unused-vars
    configureWebpack(config) {
      return {
        resolve: {
          extensionAlias: {
            '.js': ['.ts', '.js'],
            '.mjs': ['.mts', '.mjs'],
          },
        },
      };
    },
  };
}
