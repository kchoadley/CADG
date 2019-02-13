// A centralized store for shared state.
/**
 * This class creates a centralized store for shared state in the
 * GUI. It also applies middleware to the store so async fetches can be
 * made (with Thunk) and Redux DevTools (a Google Chrome extension) can
 * be utilized for testing purposes.
 *
 * Copyright 2018   Vaniya Agrawal, Ross Arcemont, Kristofer Hoadley,
 *                  Shawn Hulce, Michael McCulley
 *
 * @file store.js
 * @date February 2019
 * @authors Vaniya Agrawal
 */
import { createStore, applyMiddleware, compose } from 'redux';
import thunk from 'redux-thunk';
import rootReducer from './reducers';

const initialState = {};  // Represents the root of the store
const middleware = [
  thunk
]; // Specifies which middleware is being utilized

const store = createStore(
  rootReducer,
  initialState,
  compose(
    applyMiddleware(...middleware),
    window.__REDUX_DEVTOOLS_EXTENSION__ && window.__REDUX_DEVTOOLS_EXTENSION__()
  )
);

export default store;