/// The root reducer.
/**
 * The root reducer for the redux store. Combines all other reducers
 * from this directory into one root reducer.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley
 *                  Shawn Hulce, Michael McCulley
 *
 * @file    index.js
 * @date    February 2019
 * @authors Vaniya Agrawal
 */

import { combineReducers } from 'redux';
import adminReducer from './adminReducer';
import alertReducer from './alertReducer';
import cmspReducer from './cmspReducer';
import aogReducer from './aogReducer';

export default combineReducers({
  admins: adminReducer,
  alerts: alertReducer,
  cmsps: cmspReducer,
  aogs: aogReducer
})